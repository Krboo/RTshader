/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_intlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alelievr <alelievr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/16 23:15:31 by alelievr          #+#    #+#             */
/*   Updated: 2016/11/12 23:41:42 by alelievr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_intlen(long long int n)
{
	long long	ret;

	if (n < 0)
		n = -n;
	ret = 1;
	while (ret <= n)
		ret *= 10;
	return ((unsigned long long)(ret / 10));
}
