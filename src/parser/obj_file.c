/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_file.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yalaouf <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/03 17:51:28 by yalaouf           #+#    #+#             */
/*   Updated: 2017/05/03 20:49:13 by yalaouf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shaderpixel.h"
#include "parser.h"
#include <unistd.h>
#include <stdlib.h>
#include <sys/stat.h>

bool			check_obj_line(char *line, char *obj_name, int *indent_level)
{
	char	*k;
	int		space_number;

	space_number = 0;
	(*indent_level) = 0;
	while (*line && (*line == '\t' || *line == ' '))
	{
		if (*line == '\t')
			(*indent_level)++;
		else if (*line == ' ')
			space_number++;
		if (space_number == 4 && !(space_number = 0))
			(*indent_level)++;
		line++;
	}
	if (!*line)
		return (false);
	k = line;
	while (*line && *line++ != ':')
		;
	if (!*line)
		return (obj_file(obj_name, k));
	else
		return (false);
}

char			*format_name(char *name)
{
	char	*ret;

	ret = name;
	while (*name)
	{
		if (*name == ':')
		{
			*name = 0;
			break ;
		}
		if (!ft_isalnum(*name))
			*name = '_';
		name++;
	}
	return (ret);
}

void			display_objects(t_object *lst_obj)
{
	while (lst_obj)
	{
		if (lst_obj->children)
			display_objects(lst_obj->children);
		lst_obj = lst_obj->brother_of_children;
	}
}

bool			name_already_exists(t_object *obj, char *name)
{
	if (obj != NULL)
		return (false);
	while (obj)
	{
		if (!ft_strcmp(obj->name, name))
			return (true);
		obj = obj->brother_of_children;
	}
	return (false);
}
