/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alelievr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/03 11:51:55 by alelievr          #+#    #+#             */
/*   Updated: 2016/11/23 16:32:13 by alelievr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include <stdio.h>

char	*ft_itoa(int i)
{
	char		*buff;
	long int	n;

	buff = (char *)(char[0xF]){[0xF - 1]=0} + 0xF - 2;
	n = (i < 0 ? -(long)i : i);
	*buff-- = ((i < 0 ? -(long)i : i) % 10) + '0';
	while (n /= 10)
		if (i < 0)
			*(short *)(t_ptr)--(buff) = (short)('-' | ((n % 10 + '0') << 8));
		else
			*buff-- = (n % 10) + '0';
	return (ft_strdup(buff + (i < 0 ? 0 : 1)));
}
