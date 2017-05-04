/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbrpos.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alelievr <alelievr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/11 13:27:36 by alelievr          #+#    #+#             */
/*   Updated: 2016/01/20 15:19:03 by alelievr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdint.h>

static int		ft_intlen2(int nb)
{
	int64_t	s;
	int		r;

	s = nb;
	if (nb < 0)
		s = -nb;
	r = 0;
	while (s > 10 && ((s /= 10)))
		r++;
	if (nb < 0)
		r++;
	return (r + 1);
}

void			ft_putnbrpos(int nb, int align)
{
	int		len;
	int		i;

	i = 0;
	len = ft_intlen2(nb);
	if (align > 0)
	{
		while (i++ < align - len)
			ft_putchar(' ');
		ft_putnbr(nb);
	}
	else if (align != 0)
	{
		ft_putnbr(nb);
		while (-align > len + i++)
			ft_putchar(' ');
	}
	else
		ft_putnbr(nb);
}
