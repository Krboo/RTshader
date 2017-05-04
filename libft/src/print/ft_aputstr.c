/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_aputstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alelievr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/04 19:44:54 by alelievr          #+#    #+#             */
/*   Updated: 2015/02/07 13:45:23 by alelievr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_aputstr(unsigned char *str, size_t len)
{
	unsigned int	i;

	i = 0;
	while (i < len)
	{
		ft_putascii(str[i]);
		i++;
	}
}
