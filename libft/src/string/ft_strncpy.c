/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alelievr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/03 14:58:39 by alelievr          #+#    #+#             */
/*   Updated: 2016/03/06 19:11:06 by alelievr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strncpy(char *dst, char const *src, size_t n)
{
	size_t	size;

	size = ft_strlen(src);
	size = (size < n) ? size : n;
	ft_bzero(dst + size, n - size);
	return (ft_memcpy(dst, src, size));
}
