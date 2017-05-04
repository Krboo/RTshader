/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sscanf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmartine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/02 16:48:41 by pmartine          #+#    #+#             */
/*   Updated: 2017/05/03 20:44:07 by yalaouf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int				hexa(char *str)
{
	int	i;

	i = 1;
	if (str[i++] == 'x')
		while (ft_isdigit(str[i]) || (str[i] > 64 && str[i] < 71))
			i++;
	if (i == 8)
		return (1);
	return (0);
}

int				convert_color(char **format, char **str, FTRGB *b)
{
	if (**str == '0' && hexa(*str))
	{
		(void)(*str)++;
		(void)(*str)++;
		rgbcolor(ft_ndeconvert(*str, 16, 6), r, g, b);
	}
	(*format) += 2;
	return (1);
}

int				sscanf_return(int value, va_list *vargs)
{
	va_end(*vargs);
	return (value);
}

#define V va_arg
#define INIT_VARGS va_list s;va_start(s, str);
#define FMT_STR *f == '%' && f[1] == 's'
#define FMT_WORD *f == '%' && f[1] == 'w'
#define FMT_INT	*f == '%' && f[1] == 'd'
#define FMT_FLOAT *f == '%' && f[1] == 'f'
#define FMT_COLOR *f == '%' && f[1] == 'z'

int				ft_sscanf(char *f, char *str, ...)
{
	INIT_VARGS;
	while (42)
	{
		if (*f == '\\' && f[1] == 's')
			skip_space(&f, &str);
		if (!*str)
			break ;
		if (FMT_FLOAT && !convert_float(&f, &str, V(s, float *)))
			return (sscanf_return(-1, &s));
		if (FMT_INT && !convert_int(&f, &str, V(s, int *)))
			return (sscanf_return(-1, &s));
		if (FMT_WORD && !convert_word(&f, &str, V(s, char *), V(s, int)))
			return (sscanf_return(-1, &s));
		if (FMT_STR && !convert_str(&f, &str, V(s, char *), V(s, int)))
			return (sscanf_return(-1, &s));
		if (FMT_COLOR && !convert_color(&f, &str,
					V(s, float *), V(s, float *), V(s, float *)))
			return (sscanf_return(-1, &s));
		if (!skip_string(&f, &str))
			return (sscanf_return(-1, &s));
	}
	if (!*f)
		return (sscanf_return(0, &s));
	return (sscanf_return(-1, &s));
}
