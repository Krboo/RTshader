/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alelievr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/04 14:26:21 by alelievr          #+#    #+#             */
/*   Updated: 2016/01/20 15:04:55 by alelievr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

void	*ft_memalloc(size_t size)
{
	void			*mem;
	unsigned int	counter;
	char			*str;

	counter = 0;
	if (!(mem = (void *)malloc(sizeof(char) * size)))
		return (NULL);
	str = (char *)mem;
	if (mem != NULL)
	{
		while (counter++ < size)
			*str++ = 0;
	}
	return (mem);
}
