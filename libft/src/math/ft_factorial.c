/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_iterative_factorial.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alelievr <alelievr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/08/04 10:29:30 by alelievr          #+#    #+#             */
/*   Updated: 2014/11/27 02:44:00 by alelievr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

long	ft_factorial(int nb)
{
	long	i;

	if (nb == 0)
		return (1);
	i = 0;
	if (nb > 0)
	{
		if (nb == 1)
			return (1);
		else
		{
			i = nb * (ft_factorial(nb - 1));
			return (i);
		}
	}
	return (i);
}
