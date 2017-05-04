/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_deconvert.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alelievr <alelievr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/04 20:48:27 by alelievr          #+#    #+#             */
/*   Updated: 2016/01/20 15:11:38 by alelievr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int64_t		ft_ndeconvert(char *n, int b, int len)
{
	int64_t	buffer;

	buffer = 0;
	while (len)
		buffer += ret_base((unsigned char)*n++) * ft_pow(b, --len);
	return (buffer);
}
