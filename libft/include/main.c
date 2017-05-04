/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alelievr <alelievr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/04/01 23:14:24 by alelievr          #+#    #+#             */
/*   Updated: 2017/04/28 23:15:20 by pmartine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		main(void)
{
	const char	*table[] = {"YOLO", "OLOL", NULL};
	LIST		l;

	if (FOREACH(table, t))
		printf("%s\n", t);
	LIST_INIT(l, false);
	LIST_PUSH_BACK(l, 12);
	printf("data: %i\n", LIST_CURRENT(l, int));
}
