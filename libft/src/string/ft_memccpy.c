/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alelievr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/03 19:07:19 by alelievr          #+#    #+#             */
/*   Updated: 2016/08/08 01:13:31 by alelievr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, void const *src, int c, size_t n)
{
	size_t				i;
	unsigned char		*ptr1;
	unsigned char		*ptr2;

	ptr1 = (unsigned char*)(unsigned long)dst;
	ptr2 = (unsigned char*)(unsigned long)src;
	i = 0;
	while (i < n && ptr2[i] != (unsigned char)c)
	{
		ptr1[i] = ptr2[i];
		i++;
	}
	if (ptr2[i] == (unsigned char)c && i != n)
	{
		ptr1[i] = ptr2[i];
		return (&ptr1[i + 1]);
	}
	return (NULL);
}
