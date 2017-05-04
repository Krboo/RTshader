/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alelievr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/04 09:29:52 by alelievr          #+#    #+#             */
/*   Updated: 2017/04/28 20:27:56 by pmartine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_memcmp(void const *s1, void const *s2, size_t n)
{
	unsigned char	*u1;
	unsigned char	*u2;
	size_t			len;

	u1 = (unsigned char *)(unsigned long)s1;
	u2 = (unsigned char *)(unsigned long)s2;
	if (n >= 8)
	{
		while (!(n % 8) && n--)
			if (*u1++ != *u2++)
				return (*--u1 - *--u2);
		len = n / 8;
		while (len--)
		{
			if (*(unsigned long *)u1 != *(unsigned long *)u1)
				break ;
			u1 += 8;
			u2 += 8;
			n -= 8;
		}
	}
	while (n--)
		if (*u1++ != *u2++)
			return ((unsigned char)(*--u1 - *--u2));
	return (0);
}
