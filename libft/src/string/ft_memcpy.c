/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alelievr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/03 18:55:17 by alelievr          #+#    #+#             */
/*   Updated: 2017/04/28 20:27:02 by pmartine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *d, void const *s, size_t n)
{
	size_t			len;
	unsigned char	*dst;
	unsigned char	*src;

	dst = (unsigned char *)d;
	src = (unsigned char *)s;
	if (n >= 8)
	{
		while ((n-- % 8))
			*dst++ = *src++;
		len = n / 8;
		while (len--)
		{
			*(t_op *)dst = *(t_op *)src;
			dst += 8;
			src += 8;
		}
		n = 0;
	}
	while (n--)
		*dst++ = *src++;
	return (d);
}
