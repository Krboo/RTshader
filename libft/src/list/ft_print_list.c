/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printlist.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alelievr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/05 16:41:47 by alelievr          #+#    #+#             */
/*   Updated: 2014/11/05 17:30:57 by alelievr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_print_list(t_list *begin_list)
{
	t_list	*list;
	int		i;

	i = 0;
	list = begin_list;
	if (list != NULL)
	{
		while (list->next != NULL)
		{
			ft_putstr("maillon ");
			ft_putnbr(i);
			ft_putstr(":\n");
			ft_putstr((char *)list->content);
			ft_putstr("\n\n");
			list = list->next;
			i++;
		}
		ft_putstr("maillon ");
		ft_putnbr(i);
		ft_putstr(":\n");
		ft_putstr((char *)list->content);
		ft_putstr("\n");
	}
}
