/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alelievr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/03 18:11:28 by alelievr          #+#    #+#             */
/*   Updated: 2016/01/20 15:42:07 by alelievr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_strtrim(char const *s)
{
	char	*str;
	char	*tmp;

	while (*s == ' ' || *s == '\t' || *s == '\n')
		s++;
	if (!(str = (char *)malloc(sizeof(char) * (ft_strlen(s) + 1))))
		return (NULL);
	str = ft_strcpy(str, (char *)(unsigned long)s);
	tmp = str;
	while (*str++ != '\0')
		;
	str -= 2;
	while (*str == ' ' || *str == '\t' || *str == '\n')
		str--;
	*++str = '\0';
	return (tmp);
}
