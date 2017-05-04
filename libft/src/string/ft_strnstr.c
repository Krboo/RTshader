/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alelievr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/04 11:26:24 by alelievr          #+#    #+#             */
/*   Updated: 2016/07/27 15:59:42 by alelievr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(char const *s1, char const *s2, size_t n)
{
	unsigned int	i;
	int				j;

	j = 0;
	i = 0;
	if (s2[0] == '\0')
		return ((char *)(unsigned long)s1);
	while (s1[i] && i < n)
	{
		if (s1[i] == s2[j])
			j++;
		else
			j = 0;
		if (!s2[j])
			return ((char *)(unsigned long)s1 + (i - ((unsigned)j - 1)));
		i++;
	}
	return (NULL);
}
