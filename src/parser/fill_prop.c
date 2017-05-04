/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_prop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yalaouf <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/03 20:44:21 by yalaouf           #+#    #+#             */
/*   Updated: 2017/05/03 21:56:20 by alelievr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shaderpixel.h"
#include "parser.h"
#include <unistd.h>
#include <stdlib.h>
#include <sys/stat.h>
#include "keywords.h"

bool			obj_file(char *obj_name, char *k)
{
	if (FOREACH(g_restricted_keywords, keyword))
	{
		if (!ft_strcmp(k, keyword))
			return (false);
	}
	ft_strlcpy(obj_name, k, 256);
	return (true);
}

void			fill_prop_camera(t_camera *cam, char *line)
{
	int		ret;
	char	*str;
	char	word[256];
	int		i;

	str = (char *)(char[256]){0};
	ret = 0;
	ft_sscanf(FOV, line, &cam->fov);
	ft_sscanf(AMBIENT, line, &cam->ambient);
	if (!ft_sscanf(MASK, line, str, 256))
	{
		while ((get_next_word(&str, word)))
		{
			i = 0;
			while (ft_strcmp(g_mask_restricted_keywords[i].name, "END"))
			{
				if (!ft_strcmp(g_mask_restricted_keywords[i].name, word))
					ret |= g_mask_restricted_keywords[i].value;
				i++;
			}
		}
		cam->post_processing_mask = ret;
	}
}

void			fill_prop_primitive(t_primitive *p, char *line)
{
	char	*str;
	int		i;

	str = (char *)(char[256]){0};
	ft_sscanf(RADIUS, line, &p->radius);
	ft_sscanf(HEIGHT, line, &p->height);
	ft_sscanf(ANGLE, line, &p->angle);
	if (!ft_sscanf(TYPE, line, str, 256))
		if (FOR(i = 0, g_type_restricted_keywords[i], i++))
		{
			if (!ft_strcmp(g_type_restricted_keywords[i], ft_strupcase(str)))
				p->type = i + 1;
		}
	if (!p->type)
		ft_exit("mauvais type pour un objet\n");
	if (p->nsl < 5 && !ft_sscanf(SLICE, line, &p->slice[p->nsl].x,\
		&p->slice[p->nsl].y, &p->slice[p->nsl].z, &p->slice[p->nsl].w))
		p->nsl++;
}

void			fill_prop_material_effect(t_material *mtl, char *line)
{
	char	word[256];
	int		i;

	if (!ft_sscanf(COLOR_EFFECT, line, word, 256))
	{
		if (FOR(i = 0, g_color_effect_r_k[i].value != END, i++))
			if (!ft_strcmp(g_color_effect_r_k[i].name, word))
				mtl->color_effect = g_color_effect_r_k[i].value + 1;
	}
	if (!ft_sscanf(NORMAL_EFFECT, line, word, 256))
	{
		if (FOR(i = 0, g_normal_effect_r_k[i].value != END, i++))
			if (!ft_strcmp(g_normal_effect_r_k[i].name, word))
				mtl->normal_effect = g_normal_effect_r_k[i].value + 1;
	}
}

void			fill_prop_map(t_material *m, char *line, char *word, char *str)
{
	int		i;

	INIT(int, ret, 0);
	IINIT(char *, maps[8][3], (char *[8][3]){
		{BUMPMAP, (char *)&m->bumpmap, (char *)&m->has_bumpmap},
		{TEXTURE, (char *)&m->texture, (char *)&m->has_texture},
		{EMISSION_MAP, (char *)&m->texture, (char *)&m->has_emission_map},
		{HIGH_MAP, (char *)&m->emission_map, (char *)&m->has_highlight_map},
		{OPACITY_MAP, (char *)&m->opacity_map, (char *)&m->has_opacity_map},
		{SPECULAR_MAP, (char *)&m->specular_map, (char *)&m->has_specular_map},
		{REFL_MAP, (char *)&m->reflection_map, (char *)&m->has_reflection_map},
		{REFR_MAP, (char *)&m->refraction_map, (char *)&m->has_refraction_map},
	});
	str = (char *)(char[256]){0};
	if (FOR(i = 0, i < 2, i++))
		if (ft_sscanf(maps[i][0], line, maps[i][1], 1024))
			*(maps[i][2]) = true;
	if (!ft_sscanf(ILLUM, line, str, 256))
	{
		while (get_next_word(&str, word))
			if (FOR(i = 0, g_illum_restricted_keywords[i].value != END, i++))
				if (!ft_strcmp(g_illum_restricted_keywords[i].name, word))
					ret |= g_illum_restricted_keywords[i].value;
		m->illum = ret;
	}
}
