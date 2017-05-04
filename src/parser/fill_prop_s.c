/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_prop_s.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yalaouf <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/03 17:49:39 by yalaouf           #+#    #+#             */
/*   Updated: 2017/05/03 17:52:40 by yalaouf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shaderpixel.h"
#include "parser.h"
#include <unistd.h>
#include <stdlib.h>
#include <sys/stat.h>

void			fill_prop_vec4(t_vec4 *data, char *line)
{
	char	word[256];
	float	radius;
	float	speed;

	if (!ft_sscanf(MOVE, line, word, 256, &radius, &speed))
	{
		if (strchr(word, 'X'))
			data->x = radius;
		if (strchr(word, 'Y'))
			data->y = radius;
		if (strchr(word, 'Z'))
			data->z = radius;
		data->w = speed;
	}
	if (!ft_sscanf(ROTATE, line, word, 256, &speed))
	{
		if (strchr(word, 'X'))
			data->x = 1;
		if (strchr(word, 'Y'))
			data->y = 1;
		if (strchr(word, 'Z'))
			data->z = 1;
		data->w = speed;
	}
}

void			init_default_object(t_object *o)
{
	o->light_prop.color = (t_vec3){255, 255, 255};
	o->material.color = (t_vec3){255, 0, 255};
	o->material.specular = 0;
	o->material.opacity = 1;
	o->material.refraction = 1;
}

void			fill_prop_light(t_light *l, char *line)
{
	if (ft_sscanf(COLOR_F, line, &l->color.x, &l->color.y, &l->color.z))
		ft_sscanf(COLOR_V, line, &l->color.x, &l->color.y, &l->color.z);
	ft_sscanf(INTENSITY, line, &l->intensity);
}

void			fill_prop_transform(t_transform *t, char *line)
{
	if (!ft_sscanf(POS, line, &t->position.x, &t->position.y,\
		&t->position.z))
		t->initial_position = t->position;
	ft_sscanf(ROT, line, &t->euler_angles.x, &t->euler_angles.y,\
		&t->euler_angles.z);
}

void			fill_prop_material(t_material *mtl, char *line)
{
	char	*str;
	char	word[256];
	int		ret;
	int		i;

	str = (char *)(char[256]){0};
	ret = 0;
	i = 0;
	PALIAS(mtl->color, c);
	PALIAS(mtl->emission_color, e);
	PALIAS(mtl->highlight_color, h);
	if (ft_sscanf(COLOR_F, line, &c->x, &c->y, &c->z))
		ft_sscanf(COLOR_V, line, &c->x, &c->y, &c->z);
	if (!ft_sscanf(EMISSION_COLOR_F, line, &e->x, &e->y, &e->z))
		ft_sscanf(EMISSION_COLOR_V, line, &e->x, &e->y, &e->z);
	if (!ft_sscanf(HIGHLIGHT_COLOR_F, line, &h->x, &h->y, &h->z))
		ft_sscanf(HIGHLIGHT_COLOR_V, line, &h->x, &h->y, &h->z);
	fill_prop_material_effect(mtl, line);
	ft_sscanf(OPACITY, line, &mtl->opacity);
	ft_sscanf(SPECULAR, line, &mtl->specular);
	ft_sscanf(REFL, line, &mtl->reflection);
	ft_sscanf(REFR, line, &mtl->refraction);
	fill_prop_map(mtl, line, word, str);
}
