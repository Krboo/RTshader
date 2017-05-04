/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alelievr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/03 12:46:27 by alelievr          #+#    #+#             */
/*   Updated: 2016/01/20 15:18:27 by alelievr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_color(int n, int color)
{
	long	nb;

	nb = n;
	if (nb < 0)
	{
		ft_putchar_color('-', color);
		nb = -nb;
	}
	if (nb >= 10)
	{
		ft_putnbr_color((int)(nb / 10), color);
		ft_putnbr_color(nb % 10, color);
	}
	else
		ft_putchar_color((char)nb + '0', color);
}
