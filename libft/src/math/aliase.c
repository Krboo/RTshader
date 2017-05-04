/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aliase.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alelievr <alelievr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/19 22:52:49 by alelievr          #+#    #+#             */
/*   Updated: 2015/02/05 02:16:30 by alelievr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		aliase(int c1, int c2)
{
	unsigned char	r;
	unsigned char	g;
	unsigned char	b;

	r = ((unsigned char)(c1 >> 0) / 2) + ((unsigned char)(c2 >> 0) / 2);
	g = ((unsigned char)(c1 >> 8) / 2) + ((unsigned char)(c2 >> 8) / 2);
	b = ((unsigned char)(c1 >> 16) / 2) + ((unsigned char)(c2 >> 16) / 2);
	return (rgb(b, g, r));
}
