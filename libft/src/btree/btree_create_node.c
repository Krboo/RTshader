/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   btree_create_node.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alelievr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/08/14 12:50:35 by alelievr          #+#    #+#             */
/*   Updated: 2014/11/27 01:49:33 by alelievr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

t_btree		*btree_create_node(void *item, int index)
{
	t_btree	*tree;

	tree = malloc(sizeof(t_btree));
	tree->left = NULL;
	tree->data = item;
	tree->index = index;
	tree->right = NULL;
	tree->parent = NULL;
	return (tree);
}
