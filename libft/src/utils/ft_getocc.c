/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getocc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alelievr <alelievr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/24 16:04:11 by alelievr          #+#    #+#             */
/*   Updated: 2016/01/20 15:00:06 by alelievr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int			ft_getocc(char *str, char c, int n)
{
	int		i;
	char	*tmp;

	tmp = str;
	i = 0;
	if (str)
		while (*str)
		{
			if (*str == c)
				i++;
			if (i == n)
				return ((int)(str - tmp));
			str++;
		}
	return (-1);
}
