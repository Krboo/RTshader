/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   atlas.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmartine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/29 14:18:37 by pmartine          #+#    #+#             */
/*   Updated: 2017/05/03 22:00:15 by alelievr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "build_shader_include.h"
#include "shaderpixel.h"

unsigned int	build_atlas(t_object *obj, int atlas_w, \
	int atlas_h, bool first)
{
	t_atlas			atlas;
	int				off_x;
	int				off_y;

	off_x = 1;
	off_y = 0;
	atlas_w += 1;
	atlas.width = atlas_w;
	atlas.height = atlas_h;
	atlas.data = (unsigned char *)malloc(sizeof(int) * atlas_w * atlas_h);
	memset(atlas.data, 0, sizeof(int) * atlas_w * atlas_h);
	if (first)
		ft_memcpy(atlas.data, (unsigned char *)(char[4]){0, 0, 0, 255}, 4);
	while (obj)
	{
		add_object_textures_to_atlas(&obj->material, &atlas, &off_x, &off_y);
		if (obj->children)
			build_atlas(obj->children, atlas_w, atlas_h, false);
		obj = obj->brother_of_children;
	}
	atlas.id = new_opengl_texture(atlas_w, atlas_h, atlas.data);
	free(atlas.data);
	return (atlas.id);
}

GLuint			new_opengl_texture(int width, int height, unsigned char *data)
{
	GLuint		atlas_id;

	glGenTextures(1, &atlas_id);
	glBindTexture(GL_TEXTURE_2D, atlas_id);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, \
	GL_CLAMP_TO_BORDER);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, \
	GL_RGBA, GL_UNSIGNED_BYTE, data);
	return (atlas_id);
}

void			load_atlas(t_object *obj, char *scene_directory, \
	int *atlas_width, int *atlas_height)
{
	while (obj)
	{
		printf("\033[38;5;42mobj: %s\033[0m\n", obj->name);
		load_textures_if_exists(&obj->material, scene_directory, \
		atlas_width, atlas_height);
		if (obj->children)
			load_atlas(obj->children, scene_directory, atlas_width, \
		atlas_height);
		obj = obj->brother_of_children;
	}
}

void			add_object_textures_to_atlas(t_material *mat, t_atlas *atlas, \
	int *offset_x, int *offset_y)
{
	ADD_TEXTURE_ATLAS(mat, texture);
	ADD_TEXTURE_ATLAS(mat, bumpmap);
	ADD_TEXTURE_ATLAS(mat, emission_map);
	ADD_TEXTURE_ATLAS(mat, highlight_map);
	ADD_TEXTURE_ATLAS(mat, reflection_map);
	ADD_TEXTURE_ATLAS(mat, refraction_map);
	ADD_TEXTURE_ATLAS(mat, opacity_map);
	ADD_TEXTURE_ATLAS(mat, specular_map);
}

void			add_subimage(t_atlas *atlas, int off_x, int off_y, t_image *img)
{
	unsigned char	*begin;
	unsigned char	*imgdata;
	int				x;
	int				y;
	unsigned int	color;

	imgdata = img->data;
	x = 0;
	y = 0;
	while (y < img->height)
	{
		begin = atlas->data + (off_x * 4) + ((off_y + y) * atlas->width * 4);
		x = 0;
		while (x < img->width)
		{
			color = (*(unsigned int *)imgdata) & channeltomask(img->channels);
			*(unsigned int *)begin = color;
			begin += 4;
			imgdata += img->channels;
			x++;
		}
		y++;
	}
	free(img->data);
}
