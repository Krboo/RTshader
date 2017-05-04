/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putlong.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alelievr <alelievr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/27 21:23:47 by alelievr          #+#    #+#             */
/*   Updated: 2016/01/20 15:16:36 by alelievr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		ft_putlong(long n)
{
	unsigned long	r;

	r = (unsigned long)n;
	if (n < 0)
	{
		ft_putchar('-');
		r = (unsigned long)-n;
	}
	if (r >= 10)
	{
		ft_putlong(r / 10);
		ft_putlong(r % 10);
	}
	else
		ft_putchar('0' + (char)r);
}
