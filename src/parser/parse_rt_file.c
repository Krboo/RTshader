/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_rt_file.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmartine <pmartine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/02 21:54:21 by pmartine          #+#    #+#             */
/*   Updated: 2017/05/03 20:59:15 by yalaouf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shaderpixel.h"
#include "parser.h"
#include <unistd.h>
#include <stdlib.h>
#include <sys/stat.h>

#define ARGS2 t_object *c, char *l

void			parse_rt_file_end(int il, int no, int lt, ARGS2)
{
	if (il >= 2)
		ft_exit("max indentation reached at line: %i\n", lt);
	if (no > 300)
		ft_exit("nb max object reached at line: %i\n", lt);
	if (c == NULL)
		ft_exit("unexpected property without object: %s\n", l);
	if (il == c->indent_level + 1)
	{
		A(c, l, primitive);
		A(c, l, transform);
		A(c, l, move);
		A(c, l, rotate);
		if (c->primitive.type >= 11)
			A(c, l, light_prop);
		if (c->primitive.type == 10)
			A(c, l, camera);
		if (c->primitive.type <= 9)
			A(c, l, material);
	}
	else
		ft_exit("bad indentation at line %i\n", lt);
}

#define ARGS t_object **c, int

bool			bouc(char *l, t_scene **s, int *il, ARGS *no)
{
	t_object	*o;
	char		obj_name[256];

	o = *c;
	if (check_obj_line(l, obj_name, il))
	{
		NEW_OBJECT((*c), obj_name);
		(*c)->indent_level = (*il);
		(*s)->nb_object = ++(*no);
		if ((*s)->nb_object == 1)
		{
			(*s)->root_view = (*c);
			o = *c;
		}
		else
			o->brother_of_children = (*c);
		o = (*c);
		return (true);
	}
	return (false);
}

void			parse_rt_file(char *file, t_scene *scene)
{
	int			fd;
	char		line[0xF000 + 1];
	t_object	*c;

	c = NULL;
	INIT(int, indent_level, 0);
	INIT(int, nb_object, 0);
	INIT(int, line_count, 0);
	if ((fd = open(file, O_RDONLY)) == -1)
		ft_exit("Open Failed: %s\n", file);
	if (!file_is_regular(fd))
		ft_exit("bad file: %s\n", file);
	while (gl(line, &fd))
	{
		SKIP_EMPTY_LINE(line);
		if (bouc(line, &scene, &indent_level, &c, &nb_object))
			continue ;
		parse_rt_file_end(indent_level, nb_object, line_count, c, line);
		close(fd);
	}
}
