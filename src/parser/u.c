/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avially <avially@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/22 14:41:52 by avially           #+#    #+#             */
/*   Updated: 2017/05/03 22:41:03 by alelievr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include <sys/stat.h>

bool			check_file_extention(const char *file, const char **exts)
{
	const char	*ext;

	ext = file + strlen(file) - 1;
	while (ext != file && *ext != '.')
		ext--;
	ext++;
	while (*exts)
	{
		if (!strcmp(ext, *exts))
			return (1);
		exts++;
	}
	return (0);
}

bool			is_regular_file(const char *file)
{
	struct stat		st;

	stat(file, &st);
	return (S_ISREG(st.st_mode));
}

int				parse(int ac, char **av)
{
	t_scene		scene;

	if (ac >= 2 && av[1])
	{
		if (!check_file_extention(av[1], (const char *[]){"rt", NULL})
				|| !is_regular_file(av[1]))
			ft_exit("Invalid file: %s\n", av[1]);
		parse_rt_file(av[1], &scene);
	}
	else
		ft_exit("No file given, exiting.");
	return (1);
}
