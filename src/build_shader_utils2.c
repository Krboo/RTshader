/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_shader_utils2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmartine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/29 14:38:38 by pmartine          #+#    #+#             */
/*   Updated: 2017/05/03 21:54:43 by alelievr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "build_shader_include.h"
#include "shaderpixel.h"

void		append_post_processing(t_shader_file *shader_file, t_camera *c)
{
	if (c->post_processing_mask & BLACK_AND_WHITE)
		LIST_APPEND(shader_file->post_processing, \
	strdup("\tcolor = black_white(color);"));
	if (c->post_processing_mask & CARTOON)
		LIST_APPEND(shader_file->post_processing, \
	strdup("\tcolor = cartoon(color, vec3(0, 0, 0), h, r);"));
	if (c->post_processing_mask & NIGHT_VISION)
		LIST_APPEND(shader_file->post_processing, \
	strdup("\tcolor = nightvision(color);"));
	if (c->post_processing_mask & SEPIA)
		LIST_APPEND(shader_file->post_processing, \
	strdup("\tcolor = sepia(color);"));
	if (c->post_processing_mask & VIGNETTING)
		LIST_APPEND(shader_file->post_processing, \
	strdup("\tcolor = vignetting(color, gl_FragCoord.xy / iResolution.xy);"));
}

void		load_textures_if_exists(t_material *m, char *scene_directory, \
	int *atlas_width, int *atlas_height)
{
	LOAD_TEXTURE_ATLAS(m, texture, color, atlas_width, atlas_height);
	LOAD_TEXTURE_ATLAS(m, bumpmap, bump, atlas_width, atlas_height);
	LOAD_TEXTURE_ATLAS(m, emission_map, emission_color, atlas_width, \
	atlas_height);
	LOAD_TEXTURE_ATLAS(m, highlight_map, highlight_color, atlas_width, \
		atlas_height);
	LOAD_TEXTURE_ATLAS(m, reflection_map, reflection, atlas_width, \
		atlas_height);
	LOAD_TEXTURE_ATLAS(m, refraction_map, refraction / 10, atlas_width, \
		atlas_height);
	LOAD_TEXTURE_ATLAS(m, opacity_map, opacity, atlas_width, atlas_height);
	LOAD_TEXTURE_ATLAS(m, specular_map, specular, atlas_width, atlas_height);
	FUSION_TEXTURE_ATLAS(m, texture, opacity_map, atlas_width, atlas_height, \
	XYZ, W);
}
