/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alelievr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/03 14:32:23 by alelievr          #+#    #+#             */
/*   Updated: 2016/11/11 18:31:12 by alelievr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

int		ft_nbr_split(char *s, char c)
{
	int		cnt;
	int		in_substring;

	in_substring = 0;
	cnt = 0;
	if (s)
		while (*s != '\0')
		{
			if (in_substring == 1 && *s == c)
				in_substring = 0;
			if (in_substring == 0 && *s != c)
			{
				in_substring = 1;
				cnt++;
			}
			s++;
		}
	return (cnt);
}

int		ft_strclen(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (i);
		i++;
	}
	return (i);
}

char	**ft_strsplit(char const *s, char c)
{
	char	**ret;
	size_t	i;
	int		nb;

	if (c == 0)
		return (NULL);
	nb = ft_nbr_split((char *)(unsigned long)s, c);
	i = 0;
	ret = (char **)malloc(sizeof(char *) * ((size_t)nb + 1));
	if (ret == NULL || s == NULL)
		return (NULL);
	while (nb--)
	{
		while (*s == c && *s != '\0')
			s++;
		ret[i] = ft_strsub(s, 0, (size_t)ft_strclen((char *)
					(unsigned long)s, c));
		if (ret[i] == NULL)
			return (NULL);
		s = s + ft_strclen((char *)(unsigned long)s, c);
		i++;
	}
	ret[i] = NULL;
	return (ret);
}
