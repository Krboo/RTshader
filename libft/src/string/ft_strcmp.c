/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alelievr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/04 11:57:22 by alelievr          #+#    #+#             */
/*   Updated: 2016/10/01 19:52:27 by alelievr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_strcmp(char const *s1, char const *s2)
{
	register int					i;
	register const unsigned long	*l1 = (const unsigned long *)s1;
	register const unsigned long	*l2 = (const unsigned long *)s2;

	while (*l1 == *l2 && !LONGCHR_NULL(*l1) && !LONGCHR_NULL(*l2))
		(void)((long)(l1++) + (long)(l2++));
	i = -1;
	while (++i < 8)
		if (*((const unsigned char *)l1 + i) != *((const unsigned char *)l2 + i)
				|| !*((const unsigned char *)l1 + i)
				|| !*((const unsigned char *)l2 + i))
			return (*((const unsigned char *)l1 + i)
					- *((const unsigned char *)l2 + i));
			return (0);
}
