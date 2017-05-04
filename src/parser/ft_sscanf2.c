/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sscanf2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmartine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/02 16:48:30 by pmartine          #+#    #+#             */
/*   Updated: 2017/05/02 16:51:20 by pmartine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int		convert_float(char **format, char **str, float *f)
{
	if (!(ft_isdigit(**str) || **str == '-' || **str == '.'))
		return (0);
	else
		*f = (float)ft_atof(*str);
	while (ft_isdigit(**str) || **str == '.'
			|| **str == 'f' || **str == '-' || **str == '+')
		(void)(*str)++;
	(*format) += 2;
	return (1);
}

int		convert_int(char **format, char **str, int *i)
{
	if (!(ft_isdigit(**str)))
		return (0);
	*i = ft_atoi(*str);
	while (ft_isdigit(**str) || **str == '-')
		(void)(*str)++;
	(*format) += 2;
	return (1);
}

int		convert_word(char **format, char **str, char *ptr, int buffsize)
{
	int				len;
	const char		*begin_word = *str;

	len = 0;
	while (**str && !ft_isspace(**str)
			&& **str != ',' && **str != ':' && **str != '|')
		_((*str)++, len++);
	ft_strlcpy(ptr, begin_word, (len < buffsize + 1) ? len + 1 : buffsize);
	(*format) += 2;
	return (1);
}

int		convert_str(char **format, char **str, char *ptr, int buffsize)
{
	const char		*begin_str = *str;
	int				i;

	i = 0;
	while (**str && i < buffsize)
		_((*str)++, i++);
	ft_strlcpy(ptr, begin_str, buffsize);
	(*format) += 2;
	return (1);
}

void	rgbcolor(int color, float *r, float *g, float *b)
{
	*r = color >> 16 & 255;
	*g = color >> 8 & 255;
	*b = color & 255;
}
