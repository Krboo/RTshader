/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstrpos.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alelievr <alelievr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/11 13:43:02 by alelievr          #+#    #+#             */
/*   Updated: 2016/01/20 15:19:21 by alelievr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putstrcpos(char *s, char c, int align)
{
	int		i;
	int		len;

	i = 0;
	if (s != NULL)
	{
		len = (int)ft_strlen(s);
		if (align > 0)
		{
			while (i++ < align - len)
				ft_putchar(c);
			ft_putstr(s);
		}
		else if (align != 0)
		{
			ft_putstr(s);
			while (-align > len + i++)
				ft_putchar(c);
		}
		else
			ft_putstr(s);
	}
}
