/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sscanf3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmartine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/02 18:48:23 by pmartine          #+#    #+#             */
/*   Updated: 2017/05/02 18:48:43 by pmartine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	skip_space(char **format, char **str)
{
	(*format) += 2;
	while (ft_isspace(**str))
		(void)(*str)++;
}

int		skip_string(char **format, char **str)
{
	while (**format != '\\' && **format != '%')
	{
		if (**format != **str)
			return (0);
		else
			(void)((long)(*str)++ + (long)++(*format));
	}
	return (1);
}
