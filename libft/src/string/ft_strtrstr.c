/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrstr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alelievr <alelievr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/12 15:42:09 by alelievr          #+#    #+#             */
/*   Updated: 2016/01/20 15:42:31 by alelievr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrstr(char *dst, char *src, char *to_tr, char *tr)
{
	size_t	len;
	char	*ret;
	int		i;

	ret = dst;
	len = ft_strlen(to_tr);
	while (*src)
	{
		i = 0;
		if (!ft_strncmp(src, to_tr, len))
		{
			while (tr[i])
				*dst++ = tr[i++];
			src += len;
		}
		else
			*dst++ = *src++;
	}
	*dst = 0;
	return (ret);
}
