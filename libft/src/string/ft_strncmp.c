/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alelievr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/04 11:57:22 by alelievr          #+#    #+#             */
/*   Updated: 2016/07/27 20:21:49 by alelievr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_strncmp(char const *s1, char const *s2, size_t n)
{
	register int					i;
	register size_t					m;
	register const unsigned long	*l1 = (const unsigned long *)s1;
	register const unsigned long	*l2 = (const unsigned long *)s2;

	m = 0;
	while (*l1 == *l2 && !LONGCHR_NULL(*l1) && !LONGCHR_NULL(*l2) && m + 8 < n)
		(void)((long)(l1++) + (long)(l2++) + (long)(m += 8));
	i = -1;
	m--;
	while (++i < 8 && ++m < n)
		if (*((const unsigned char *)l1 + i) != *((const unsigned char *)l2 + i)
				|| !*((const unsigned char *)l1 + i)
				|| !*((const unsigned char *)l2 + i))
			return (*((const unsigned char *)l1 + i)
					- *((const unsigned char *)l2 + i));
			return (0);
}
