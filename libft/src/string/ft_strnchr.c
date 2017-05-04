/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alelievr <alelievr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/24 21:18:37 by alelievr          #+#    #+#             */
/*   Updated: 2016/01/20 15:30:18 by alelievr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnchr(char const *s, int c, int n)
{
	while (*s != (char)c && *s != '\0' && n--)
		s++;
	if (*s == (char)c)
		return ((char *)(unsigned long)s);
	return (NULL);
}
