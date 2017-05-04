/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alelievr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/07 01:37:04 by alelievr          #+#    #+#             */
/*   Updated: 2016/01/20 15:50:54 by alelievr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		ft_nbr_lstsplit(char *s, char c)
{
	int		i;

	i = 0;
	while (*s != '\0')
	{
		while (*s && *s == c)
			s++;
		while (*s && *s != c)
			s++;
		i++;
	}
	return (i);
}

static int		ft_lstclen(char *str, char c)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (i);
		i++;
	}
	return (i);
}

t_list			*ft_lstsplit(char *s, char c)
{
	t_list	*list;
	t_list	*begin_list;
	size_t	i;
	int		nb;

	nb = ft_nbr_lstsplit(s, c);
	i = 0;
	if (s == NULL)
		return (NULL);
	while (nb--)
	{
		while (*s == c && *s != '\0')
			s++;
		list = ft_lstnew(ft_strsub((const char *)s, 0,
					(size_t)ft_lstclen((char *)s,
						c)), (size_t)ft_lstclen((char *)s, c));
		if (list == NULL)
			return (NULL);
		ft_lsteadd(&begin_list, list);
		s = s + ft_lstclen((char *)s, c);
		i++;
	}
	ft_lstadd(&begin_list, ft_lstnew(NULL, 0));
	return (begin_list->next);
}
