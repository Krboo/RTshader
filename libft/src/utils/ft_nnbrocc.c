/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nbrocc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alelievr <alelievr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/07 18:56:17 by alelievr          #+#    #+#             */
/*   Updated: 2015/03/07 19:24:33 by alelievr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_nnbrocc(char *str, char c, int len)
{
	int		i;

	i = 0;
	if (str && c)
	{
		while (*str && len-- > 0)
		{
			if (*str == c)
				i++;
			str++;
		}
	}
	return (i);
}
