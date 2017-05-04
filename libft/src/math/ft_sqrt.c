/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sqrt.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alelievr <alelievr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/04/02 16:52:12 by alelievr          #+#    #+#             */
/*   Updated: 2016/01/20 15:20:34 by alelievr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

double			ft_sqrt(int nb)
{
	double		result;
	double		diff;

	if ((double)nb == 0.0 || (double)nb == 1.0)
		return ((double)nb);
	result = (double)nb;
	diff = result;
	result = 0.5 * (result + (double)nb / result);
	while (!cmp_float(result, diff))
	{
		diff = result;
		result = 0.5 * (result + (double)nb / result);
	}
	return (result);
}
