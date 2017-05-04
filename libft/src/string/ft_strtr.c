/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtr.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alelievr <alelievr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/09 18:04:01 by alelievr          #+#    #+#             */
/*   Updated: 2015/03/09 18:06:33 by alelievr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtr(char *str, char src, char dst)
{
	char	*ret;

	ret = str;
	if (str)
		while (*str)
		{
			if (*str == src)
				*str = dst;
			str++;
		}
	return (ret);
}
