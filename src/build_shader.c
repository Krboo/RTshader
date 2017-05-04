/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_shader.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmartine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/29 13:39:08 by pmartine          #+#    #+#             */
/*   Updated: 2017/05/03 23:02:20 by alelievr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shaderpixel.h"
#include "parser.h"
#include <sys/stat.h>
#include <string.h>
#include <unistd.h>
#include "build_shader_include.h"
#include <errno.h>

static void		init_shader_file(t_shader_file *shader_file)
{
	if (!(shader_file->begin = NEW_LINE_LIST))
		ft_exit("malloc error !");
	LIST_APPEND(shader_file->begin, strdup(g_fragment_shader_text));
	shader_file->uniform_begin = shader_file->begin;
	shader_file->function_begin = shader_file->begin;
	LIST_APPEND(shader_file->function_begin, strdup("/* Static funcs */\n"));
	LIST_APPEND(shader_file->function_begin, strdup(g_shader_header_text));
	shader_file->main_image_begin = shader_file->function_begin;
	shader_file->scene_begin = shader_file->function_begin;
	LIST_INSERT(shader_file->scene_begin, strdup("/* Generated scene from\
	parser */\n"));
	shader_file->scene_end = shader_file->scene_begin->next;
	LIST_APPEND(shader_file->scene_begin, strdup(g_scene_start_text));
	LIST_APPEND(shader_file->scene_end, strdup(g_scene_end_text));
	shader_file->raytrace_lights = shader_file->scene_end;
	LIST_APPEND(shader_file->raytrace_lights, strdup(g_raytrace_start_text));
	LIST_INSERT(shader_file->raytrace_lights, strdup(g_raytrace_end_text));
	shader_file->post_processing = shader_file->raytrace_lights;
	LIST_APPEND(shader_file->main_image_begin, strdup("\n/* \
	Static MainImage */\n"));
	LIST_APPEND(shader_file->main_image_begin, strdup(g_main_image_start_text));
	LIST_APPEND(shader_file->uniform_begin, strdup("/*Generated uniforms*/\n"));
}

static void		load_essencial_files(t_shader_file *shader_file,
		t_file *sources)
{
	const char *const	*files = (const char *const[]){SHADERS};
	int					fd;
	char				line[0xF000];
	int					i;

	i = 0;
	while (*files)
	{
		if ((fd = open(*files, O_RDONLY)) == -1)
		{
			printf("open error on [%s]: %s", *files, strerror(errno));
			exit(-1);
		}
		if (!file_is_regular(fd))
			ft_exit("bad file type: %s\n", *files);
		while (gl(line, &fd))
			LIST_APPEND(shader_file->function_begin, strdup(line));
		close(fd);
		strcpy(sources[i++].path, *files);
		files++;
	}
}

static char		*concat_line_list(t_shader_file *shader_file)
{
	static char		buff[MAX_SHADER_FILE_SIZE + 1];
	t_line_list		*line;
	t_line_list		*prev;

	INIT(int, index, 0);
	line = shader_file->begin;
	while (line)
	{
		if (line->line == NULL)
		{
			DBA(prev, line, line, line->next);
			free(prev);
			continue ;
		}
		if (index + strlen(line->line) >= MAX_SHADER_FILE_SIZE)
			ft_exit("max shader file reached !\n");
		strcpy(buff + index, line->line);
		index += strlen(line->line);
		free(line->line);
		buff[index++] = '\n';
		DBA(prev, line, line, line->next);
		free(prev);
	}
	return (buff);
}

static void		tree_march(t_shader_file *shader_file, t_object *obj)
{
	int		n_light;
	char	line[0xF000];

	n_light = 0;
	while (obj)
	{
		if (obj->primitive.type == CAMERA + 1)
			append_post_processing(shader_file, &obj->camera);
		if (ISLIGHT)
			n_light++;
		append_uniforms(shader_file, obj);
		LIST_APPEND(shader_file->scene_begin, generate_scene_line(obj));
		if (obj->children)
			tree_march(shader_file, obj->children);
		obj = obj->brother_of_children;
	}
	if (n_light == 0)
	{
		sprintf(line, "\tcolor += calc_color(r, vec3(%f, %f, %f), \
		vec3(%f, %f, %f), %f);", 0.f, 0.f, 0.f, 1.f, 1.f, 1.f, 0.f);
		LIST_APPEND(shader_file->raytrace_lights, strdup(line));
	}
}

char			*build_shader(t_scene *root, char *scene_directory, \
	int *atlas_id, t_file *sources)
{
	t_shader_file		shader_file;
	int					atlas_width;
	int					atlas_height;

	atlas_width = 0;
	atlas_height = 0;
	init_shader_file(&shader_file);
	load_essencial_files(&shader_file, sources);
	load_atlas(root->root_view, scene_directory, &atlas_width, &atlas_height);
	*atlas_id = build_atlas(root->root_view, atlas_width, atlas_height, true);
	tree_march(&shader_file, root->root_view);
	return (concat_line_list(&shader_file));
}
