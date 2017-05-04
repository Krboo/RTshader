/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alelievr <alelievr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/13 23:36:10 by alelievr          #+#    #+#             */
/*   Updated: 2017/04/21 19:09:53 by pmartine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shaderpixel.h"
#include <sys/stat.h>

bool	file_is_regular(int fd) __attribute__((overloadable))
{
	struct stat		st;

	fstat(fd, &st);
	return (S_ISREG(st.st_mode));
}

bool	file_is_regular(char *path) __attribute__((overloadable))
{
	struct stat		st;

	stat(path, &st);
	return (S_ISREG(st.st_mode));
}
