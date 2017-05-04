/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_word.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmartine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/22 19:43:38 by pmartine          #+#    #+#             */
/*   Updated: 2017/04/22 19:44:45 by pmartine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int		get_next_word(char **str, char *res)
{
	char *b;

	b = *str;
	if (!**str)
		return (0);
	while (ft_isspace(**str) && **str)
		(*str)++;
	if (!**str)
		return (0);
	while (!ft_isspace(**str) && **str)
		*res++ = *(*str)++;
	*res = 0;
	return (*str - b);
}
