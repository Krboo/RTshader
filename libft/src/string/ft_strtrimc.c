/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrimc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alelievr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/03 18:11:28 by alelievr          #+#    #+#             */
/*   Updated: 2016/01/20 15:42:16 by alelievr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_strtrimc(char const *s, char c)
{
	char	*str;
	char	*tmp;

	while (*s == c || *s == '\t' || *s == '\n')
		s++;
	str = (char *)malloc(sizeof(char) * (ft_strlen(s) + 1));
	if (str == NULL)
		return (NULL);
	str = ft_strcpy(str, (char *)(unsigned long)s);
	tmp = str;
	while (*str++ != '\0')
		;
	str -= 2;
	while (*str == c || *str == '\t' || *str == '\n')
		str--;
	*++str = '\0';
	return (tmp);
}
