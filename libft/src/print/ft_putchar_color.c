/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar_color.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alelievr <alelievr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/23 12:23:31 by alelievr          #+#    #+#             */
/*   Updated: 2015/01/23 12:28:33 by alelievr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putchar_color(char c, int color)
{
	ft_putstr("\033[38;5;");
	ft_putnbr(color);
	ft_putchar('m');
	ft_putchar(c);
}
