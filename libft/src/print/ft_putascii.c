/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putascci.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alelievr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/04 19:42:17 by alelievr          #+#    #+#             */
/*   Updated: 2015/02/07 13:45:49 by alelievr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putascii(unsigned char c)
{
	ft_putchar('\\');
	if (c == 0)
		ft_putstr("000");
	else if (c < 10)
	{
		ft_putstr("00");
		ft_putnbr((int)c);
	}
	else if (c < 100)
	{
		ft_putchar('0');
		ft_putnbr((int)c);
	}
	else
		ft_putnbr((int)c);
	ft_putchar(' ');
}
