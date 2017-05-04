/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alelievr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/03 17:31:53 by alelievr          #+#    #+#             */
/*   Updated: 2016/10/05 20:17:22 by alelievr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#define MEM_FILL(x, y) x[0]=y;x[1]=y;x[2]=y;x[3]=y;x[4]=y;x[5]=y;x[6]=y;x[7]=y
#define OP_SIZE sizeof(long)

void	ft_bzero(void *b, size_t len)
{
	register unsigned long	dstp;
	register size_t			xlen;

	dstp = (unsigned long)b;
	if (len >= 8)
	{
		while (dstp % OP_SIZE != 0)
			DBI(*((unsigned char *)dstp++) = 0, --len);
		xlen = len / (OP_SIZE * 8) + 1;
		while (--xlen > 0)
			DBI(MEM_FILL(((unsigned long *)dstp), 0llu), dstp += 8 * OP_SIZE);
		len %= OP_SIZE * 8;
		xlen = len / OP_SIZE + 1;
		while (--xlen > 0)
			_(*((unsigned long *)dstp) = 0llu, dstp += OP_SIZE);
		len %= OP_SIZE;
	}
	while (len > 0)
		_(*((unsigned char *)dstp++) = 0, --len);
}
