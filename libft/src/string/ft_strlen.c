/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alelievr <alelievr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/01 17:47:34 by alelievr          #+#    #+#             */
/*   Updated: 2016/10/01 19:41:06 by alelievr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include "libft.h"

size_t	ft_strlen(char const *s)
{
	const char			*begin = s;
	unsigned long		*str;
	const char			*cp;

	while (((unsigned long int)s & (sizeof(long) - 1)) != 0)
		if (*s++ == '\0')
			return (s - begin - 1);
	str = (unsigned long *)(unsigned long)s;
	while (42)
	{
		if ((LONGCHR_NULL(*str++)))
		{
			cp = (const char *)(str - 1);
			IFRET__(cp[0] == 0, cp - begin);
			IFRET__(cp[1] == 0, cp - begin + 1);
			IFRET__(cp[2] == 0, cp - begin + 2);
			IFRET__(cp[3] == 0, cp - begin + 3);
			IFRET__(cp[4] == 0, cp - begin + 4);
			IFRET__(cp[5] == 0, cp - begin + 5);
			IFRET__(cp[6] == 0, cp - begin + 6);
			IFRET__(cp[7] == 0, cp - begin + 7);
		}
	}
	return (0);
}
