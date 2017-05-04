/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_shr.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alelievr <alelievr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/23 20:31:04 by alelievr          #+#    #+#             */
/*   Updated: 2015/02/24 23:10:34 by alelievr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_shr(char *str, int n)
{
	char	*tmp;

	tmp = str;
	if (!str)
		return (0);
	if (!n)
		return (str);
	while (n--)
	{
		str = tmp;
		while (*str)
		{
			*str = str[1];
			str++;
		}
		*str = 0;
	}
	return (tmp);
}
