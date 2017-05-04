/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alelievr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/03 19:30:23 by alelievr          #+#    #+#             */
/*   Updated: 2016/11/12 23:47:10 by alelievr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(void const *src, int c, size_t n)
{
	size_t				len;
	unsigned long		r_c;
	const unsigned char	*s = src;

	if (n >= 8)
	{
		r_c = (unsigned long)((unsigned char)c | ((unsigned char)c << 8));
		r_c |= r_c << 16;
		r_c |= r_c << 32;
		while (!(n % 8))
		{
			if (*(const unsigned char *)s++ == (unsigned char)c)
				return ((void *)--s);
			n--;
		}
		len = n / 8;
		n += 8;
		while (len-- && ((n -= 8) || 1))
			if (LONGCHR(*(unsigned long *)(unsigned long)s, r_c))
				break ;
	}
	while (n--)
		if (*(const unsigned char *)s++ == (unsigned char)c)
			return ((void *)(unsigned long)--s);
	return (NULL);
}
