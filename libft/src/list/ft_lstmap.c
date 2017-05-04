/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ft_lstmap.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alelievr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/06 11:25:03 by alelievr          #+#    #+#             */
/*   Updated: 2015/11/27 23:11:57 by alelievr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list		*list;
	t_list		*begin_list;
	t_list		*tmp;

	if (f == NULL)
		return (NULL);
	if (!(tmp = f(lst)))
		return (NULL);
	if (!(list = ft_lstnew(tmp->content, tmp->content_size)))
		return (NULL);
	begin_list = list;
	while (lst->next != NULL)
	{
		if (!(tmp = f(lst->next)))
			return (NULL);
		if (!(list->next = ft_lstnew(tmp->content, tmp->content_size)))
			return (NULL);
		lst = lst->next;
		list = list->next;
	}
	return (begin_list);
}
