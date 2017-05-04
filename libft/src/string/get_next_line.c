/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test5.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alelievr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/11 19:30:19 by alelievr          #+#    #+#             */
/*   Updated: 2016/01/20 15:46:43 by alelievr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "libft.h"

static int		ft_strocc(char **occ, char *tmp)
{
	if (*occ != NULL)
	{
		**occ = '\0';
		*occ += 1;
		ft_strcpy(tmp, *occ);
		return (1);
	}
	else
		return (0);
}

static char		*ft_reloc(char **line, int *ret)
{
	char	*str;

	str = (char *)malloc(sizeof(char) * (ft_strlen(*line) + (size_t)*ret + 1u));
	if (str == NULL)
		return (NULL);
	str = ft_strcpy(str, *line);
	free(*line);
	return (str);
}

static int		retu(int r1, int r2)
{
	if (r1 == 1)
		return (1);
	if (r2 == 0)
		return (0);
	else
		return (-1);
}

int				get_next_line(int const fd, char **line)
{
	char		buf[BUFF_SIZE + 1];
	int			ret;
	static char	tmp[256][BUFF_SIZE];
	char		*occ;

	ret = 0;
	if (line == NULL || fd < 0)
		return (-1);
	*line = (char *)malloc(sizeof(char) * (BUFF_SIZE + ft_strlen(tmp[fd]) + 1));
	if (*line == NULL)
		return (-1);
	*line = ft_strcpy(*line, tmp[fd]);
	while (((occ = ft_strchr(*line, '\n')) == NULL)
			&& ((ret = (int)read(fd, buf, BUFF_SIZE)) > 0))
	{
		buf[ret] = '\0';
		if ((*line = ft_reloc(line, &ret)) == NULL)
			return (-1);
		ft_strcat(*line, buf);
	}
	occ = ft_strchr(*line, '\n');
	return (retu(ft_strocc(&occ, tmp[fd]), ret));
}
