/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putdouble.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alelievr <alelievr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/27 21:19:27 by alelievr          #+#    #+#             */
/*   Updated: 2016/01/20 15:15:55 by alelievr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

void	ft_putdouble(double d)
{
	int		len;
	char	*s;
	char	*tmp;

	ft_putnbr((int)d);
	if (!cmp_float(d, (int)d))
	{
		ft_putchar('.');
		d -= (int)d;
		d *= 1000000000;
		if (!(s = ft_itoa((int)d)))
			return ;
		len = (int)ft_strlen(s) - 1;
		while (s[len] == '0')
			len--;
		if (!(tmp = ft_strsub(s, 0, (size_t)len + 1)))
			return ;
		d = ft_atoi(tmp);
		ft_putnbr((int)d);
		free(s);
		free(tmp);
	}
}
