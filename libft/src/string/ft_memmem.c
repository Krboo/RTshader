/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmem.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alelievr <alelievr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/02 22:28:05 by alelievr          #+#    #+#             */
/*   Updated: 2016/01/20 15:10:23 by alelievr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmem(void *a, char *str, size_t len)
{
	char			*tmp;
	unsigned long	addr;

	addr = (unsigned long)a;
	tmp = str;
	while (len--)
	{
		if (*str == *(char *)addr)
			str++;
		else
			str = tmp;
		if (!*str)
			return ((void *)(addr - ft_strlen(tmp)));
		addr++;
	}
	return (NULL);
}
