/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplitstr.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alelievr <alelievr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/06 12:37:47 by alelievr          #+#    #+#             */
/*   Updated: 2016/01/20 15:50:59 by alelievr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static int		ft_nbr_splitstr(char *s, char *c)
{
	int		cnt;
	int		in_substring;

	in_substring = 0;
	cnt = 0;
	if (s)
		while (*s != '\0')
		{
			if (in_substring == 1 && ft_strchr(c, *s))
				in_substring = 0;
			if (in_substring == 0 && ft_strchr(c, *s))
			{
				in_substring = 1;
				cnt++;
			}
			s++;
		}
	return (cnt);
}

static int		ft_strclenstr(char *str, char *c)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (ft_strchr(c, str[i]))
			return (i);
		i++;
	}
	return (i);
}

char			**ft_strsplitstr(char const *s, char *c)
{
	char	**ret;
	size_t	i;
	int		nb;

	if (s == NULL || c == NULL)
		return (NULL);
	nb = ft_nbr_splitstr((char *)(unsigned long)s, c);
	i = 0;
	ret = (char **)malloc(sizeof(char *) * ((size_t)nb + 1));
	if (ret == NULL || s == NULL)
		return (NULL);
	while (nb--)
	{
		while (ft_strchr(c, *s) && *s != '\0')
			s++;
		ret[i] = ft_strsub(s, 0, (size_t)ft_strclenstr((char *)
					(unsigned long)s, c));
		if (ret[i] == NULL)
			return (NULL);
		s = s + ft_strclenstr((char *)(unsigned long)s, c);
		i++;
	}
	ret[i] = NULL;
	return (ret);
}
