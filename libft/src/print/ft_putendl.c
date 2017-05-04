/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alelievr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/03 14:21:41 by alelievr          #+#    #+#             */
/*   Updated: 2015/11/27 23:22:35 by alelievr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putendl(char const *s)
{
	int	i;

	i = 0;
	if (s != NULL)
		while (s[i])
		{
			ft_putchar(s[i]);
			i++;
		}
	else
		ft_putstr("(null)");
	ft_putchar('\n');
}
