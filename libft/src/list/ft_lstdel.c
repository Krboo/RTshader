/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alelievr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/06 23:39:39 by alelievr          #+#    #+#             */
/*   Updated: 2014/11/25 20:36:39 by alelievr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

void	ft_lstdel(t_list **alst, void (*del)(void *, size_t))
{
	t_list	*next_lst;
	t_list	*temp;

	if (alst != NULL || del != NULL)
	{
		next_lst = *alst;
		while (next_lst != NULL)
		{
			if (del != NULL)
				(*del)(next_lst->content, (*next_lst).content_size);
			temp = next_lst->next;
			free(next_lst);
			next_lst = temp;
		}
		*alst = NULL;
	}
}
