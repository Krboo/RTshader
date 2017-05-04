/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nmatch.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alelievr <alelievr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/06 12:41:09 by alelievr          #+#    #+#             */
/*   Updated: 2016/01/20 14:53:03 by alelievr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_nmatch(char *s1, char *s2)
{
	if (*s2 == '*')
		return (!*s1 ? ft_nmatch(s1, s2 + 1) :
				ft_nmatch(s1, s2 + 1) + ft_nmatch(s1 + 1, s2));
		if (!*s1)
		return (*s2 ? 0 : 1);
	return (*s1 == *s2 ? ft_nmatch(s1 + 1, s2 + 1) : 0);
}
