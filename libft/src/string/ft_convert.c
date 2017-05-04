/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_convert.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alelievr <alelievr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/03 19:11:48 by alelievr          #+#    #+#             */
/*   Updated: 2016/01/20 14:57:41 by alelievr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <stdio.h>
#include <stdint.h>
#include "libft.h"

int		ft_convert(char *buffer, int64_t n, int b, int maj)
{
	static char		base[] = "0123456789ABCDEF";
	int				i;
	int64_t			tmp;

	i = 0;
	tmp = n;
	while (tmp >= b && ((tmp /= b) || 1))
		i++;
	while (n >= b && ((buffer[i--] = base[n % b] + ((!maj && base[n % b]
							>= 'A') ? 32 : 0)) || 1))
		n /= b;
	buffer[i] = base[n % b] + ((!maj && base[n % b] >= 'A') ? 32 : 0);
	return ((int)ft_strlen(buffer));
}
