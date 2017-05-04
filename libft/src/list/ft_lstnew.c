/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alelievr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/05 16:39:31 by alelievr          #+#    #+#             */
/*   Updated: 2016/01/20 15:01:28 by alelievr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "stdlib.h"

t_list	*ft_lstnew(void const *content, size_t content_size)
{
	void	*ptr;
	t_list	*list;

	ptr = (void *)malloc(sizeof(char) * (content_size));
	list = (t_list *)malloc(sizeof(t_list));
	if (list == NULL || ptr == NULL)
		return (NULL);
	if (content == NULL)
	{
		list->content = NULL;
		list->content_size = 0;
	}
	else
	{
		list->content = (void *)ft_memcpy(ptr, content, content_size);
		list->content_size = content_size;
	}
	return (list);
}
