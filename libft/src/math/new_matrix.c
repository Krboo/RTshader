/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_matrix.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alelievr <alelievr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/02 00:58:10 by alelievr          #+#    #+#             */
/*   Updated: 2016/01/20 15:49:01 by alelievr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

t_matrix	*new_matrix(int h, int w, double **m)
{
	t_matrix	*ma;
	int			i;
	int			j;

	i = 0;
	ma = (t_matrix *)malloc(sizeof(t_matrix));
	ma->m = (double **)malloc(sizeof(double *) * (size_t)h);
	ma->w = w;
	ma->h = h;
	while (i < h)
	{
		ma->m[i] = (double *)malloc(sizeof(double) * (size_t)w);
		j = 0;
		while (j < w)
		{
			ma->m[i][j] = m[i][j];
			j++;
		}
		i++;
	}
	free(m);
	return (ma);
}
