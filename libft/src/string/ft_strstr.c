/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alelievr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/04 11:26:24 by alelievr          #+#    #+#             */
/*   Updated: 2016/03/21 22:17:31 by alelievr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(char const *s1, char const *s2)
{
	int		i;
	int		j;
	int		c;

	i = 0;
	c = 0;
	if (s2[0] == '\0')
		return (char*)(unsigned long)(s1);
	while (s1[i] != '\0')
	{
		j = i;
		c = 0;
		while (s1[j] == s2[c] && s1[j++] && s2[c++])
			if (s2[c] == '\0')
				return (char*)(unsigned long)(&s1[i]);
		i++;
	}
	return (NULL);
}
