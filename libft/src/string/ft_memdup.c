/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alelievr <alelievr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/27 02:05:33 by alelievr          #+#    #+#             */
/*   Updated: 2014/11/27 02:32:14 by alelievr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_memdup(char *s, unsigned int size)
{
	char	*new;

	if (s == NULL)
		return (NULL);
	if ((new = ft_memnew(size)) == NULL)
		return (NULL);
	ft_memcpy(new, s, size);
	return (new);
}
