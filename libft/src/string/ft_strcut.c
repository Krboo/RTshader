/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcut.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alelievr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/03 18:16:41 by alelievr          #+#    #+#             */
/*   Updated: 2016/01/20 15:21:56 by alelievr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_strcut(char const *s, int n)
{
	unsigned int	i;
	char			*str;

	str = (char *)malloc(sizeof(char) * ft_strlen(s));
	if (str == NULL)
		return (NULL);
	i = 0;
	if (n >= 0)
	{
		str = (char *)(unsigned long)&s[n];
		return (str);
	}
	else
	{
		while (s[i] && i < (unsigned int)ft_strlen(s) + (unsigned)n)
		{
			str[i] = s[i];
			i++;
		}
		str[i] = '\0';
		return (str);
	}
}
