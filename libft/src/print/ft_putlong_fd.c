/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putlong.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alelievr <alelievr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/27 21:23:47 by alelievr          #+#    #+#             */
/*   Updated: 2016/01/20 15:16:58 by alelievr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		ft_putlong_fd(long n, int fd)
{
	unsigned long	r;

	r = (unsigned long)n;
	if (n < 0)
	{
		ft_putchar_fd('-', fd);
		r = (unsigned long)-n;
	}
	if (r >= 10)
	{
		ft_putlong_fd(r / 10, fd);
		ft_putlong_fd(r % 10, fd);
	}
	else
		ft_putchar_fd('0' + (char)r, fd);
}
