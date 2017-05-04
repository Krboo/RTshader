/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pow.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alelievr <alelievr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/03 20:02:44 by alelievr          #+#    #+#             */
/*   Updated: 2016/01/20 15:12:22 by alelievr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdint.h>

int64_t	ft_pow(int64_t n, int pow)
{
	int64_t	tmp;

	tmp = n;
	if (pow == 1)
		return (n);
	if (pow == 0)
		return (1);
	if (pow > 0)
		while (--pow)
			n *= tmp;
	return (n);
}
