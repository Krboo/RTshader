/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_shr.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alelievr <alelievr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/23 20:08:21 by alelievr          #+#    #+#             */
/*   Updated: 2016/01/20 15:20:02 by alelievr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_shl(char *str, int n)
{
	char	*tmp;
	int		len;
	int		l;

	len = 0;
	if (!str)
		return (0);
	if (!n)
		return (str);
	tmp = str;
	len = (int)ft_strlen(str);
	while (n--)
	{
		l = len;
		str++;
		while (*str++)
			;
		while (l--)
		{
			str--;
			*str = str[-1];
		}
	}
	return (tmp);
}
