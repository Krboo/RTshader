/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memswap.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alelievr <alelievr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/27 02:25:14 by alelievr          #+#    #+#             */
/*   Updated: 2015/02/17 20:10:50 by alelievr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <string.h>

void	ft_memswap(void *d1, void *d2, size_t size)
{
	char		*s1;
	char		*end;
	char		*s2;
	char		tmp;

	s2 = d2;
	s1 = d1;
	end = s1 + size;
	while (s1 < end)
	{
		tmp = *s1;
		*s1 = *s2;
		*s2 = tmp;
		s1++;
		s2++;
	}
}
