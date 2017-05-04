/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alelievr <alelievr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/01 17:24:22 by alelievr          #+#    #+#             */
/*   Updated: 2016/11/16 03:14:02 by alelievr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>
#include <string.h>
#define MEM_FILL(x, y) x[0]=y;x[1]=y;x[2]=y;x[3]=y;x[4]=y;x[5]=y;x[6]=y;x[7]=y
#define OP_SIZE sizeof(long)

void	*ft_memset(void *b, int c, size_t len)
{
	register unsigned long	dstp;
	register size_t			xlen;
	register unsigned long	cccc;

	dstp = (unsigned long)b;
	if (len >= 8)
	{
		cccc = (unsigned char)c;
		cccc |= cccc << 8;
		cccc |= cccc << 16;
		cccc |= (cccc << 16) << 16;
		while (dstp % OP_SIZE != 0)
			DBI(*((unsigned char *)dstp++) = c, --len);
		xlen = len / (OP_SIZE * 8) + 1;
		while (--xlen > 0)
			DBI(MEM_FILL(((unsigned long *)dstp), cccc), dstp += 8 * OP_SIZE);
		len %= OP_SIZE * 8;
		xlen = len / OP_SIZE + 1;
		while (--xlen > 0)
			_(*((unsigned long *)dstp) = cccc, dstp += OP_SIZE);
		len %= OP_SIZE;
	}
	while (len > 0)
		_(*((unsigned char *)dstp++) = c, --len);
	return (b);
}
