/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memocc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alelievr <alelievr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/12 16:47:55 by alelievr          #+#    #+#             */
/*   Updated: 2015/03/12 16:50:57 by alelievr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_memocc(void *mem, char *occ, int n)
{
	char	*str;
	int		ret;

	ret = 0;
	str = mem;
	while (n--)
	{
		if (!ft_strncmp(str, occ, ft_strlen(occ)))
			ret++;
		str++;
	}
	return (ret);
}
