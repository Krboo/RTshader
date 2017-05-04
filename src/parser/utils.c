/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmartine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/02 16:49:21 by pmartine          #+#    #+#             */
/*   Updated: 2017/05/02 16:49:24 by pmartine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include <unistd.h>

int				gl(char *dst, int *fd)
{
	static char buff[0xF000 + 1];
	static char *ptr = buff;
	char		*nl;
	int			r;

	r = 0;
	if ((long)ptr == 0x1l)
		ptr = buff;
	if (!(nl = ft_strchr(ptr, '\n')))
	{
		if (ptr != buff)
		{
			ft_strcpy(buff, ptr);
			ptr = buff + (sizeof(buff) - (ptr - buff)) - 1;
		}
		r = read(*fd, ptr, (sizeof(buff) - (ptr - buff) - 1));
		ptr[r] = '\0';
		ptr = buff;
	}
	if ((nl = ft_strchr(ptr, '\n')))
		ft_strlcpy(dst, ptr, nl - ptr + 1);
	ptr = nl + 1;
	return (!!nl);
}
