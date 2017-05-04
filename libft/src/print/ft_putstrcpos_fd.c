/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstrpos.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alelievr <alelievr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/11 13:43:02 by alelievr          #+#    #+#             */
/*   Updated: 2016/01/20 15:19:37 by alelievr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putstrcpos_fd(char *s, char c, int align, int fd)
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
				ft_putchar_fd(c, fd);
			ft_putstr_fd(s, fd);
		}
		else if (align != 0)
		{
			ft_putstr_fd(s, fd);
			while (-align > len + i++)
				ft_putchar_fd(c, fd);
		}
		else
			ft_putstr_fd(s, fd);
	}
}
