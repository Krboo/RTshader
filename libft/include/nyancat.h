/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nyancat.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alelievr <alelievr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/12 23:52:18 by alelievr          #+#    #+#             */
/*   Updated: 2017/05/03 20:38:26 by yalaouf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NYANCAT_H
# define NYANCAT_H

# include <stdbool.h>

/*
**	Utils:
*/

# define CONCAT(x, y)	x##y
# define STRINGYFY(x)	#x
# define ALIAS(x, y)	typeof(x) y = x;
# define PALIAS(x, y)	typeof(x) *y = &(x);
# define FOR(a, b, c)	0){;} for ((a); (b); (c)
# define FOREACH(x,y) 0){;}int __##x=0;typeof(*x)y;for(y=*x;(y=x[__##x]);__##x++
# define SHORTIFY(c)	((long)c | ((long)c << 8))
# define INTIFY(c)		(SHORTIFY(c) | (SHORTIFY(c) << 16))
# define LONGIFY(c)		(INTIFY(c) | (INTIFY(c) << 32))
# define GOTO(x)		goto x
# define TER(x, y, z)	((x) ? (y) : (z))

/*
**	Static linked lists:
*/

# define PUSH_FRONT(x, y)	(t_list[]){{x,y}}
# define PUSH_AFTER(x, y)	((!y) ? (0) : (y->next = (t_list[]){{x, y->next}}))
# define PUSH_BACK(x, y)	TO_END(y);PUSH_AFTER(x, t)
# define TO_END(y)			t = y;while((t=t->next)->next);
# define POP_FRONT(y)		y = y->next;
# define POP_BACK(y)		t=y;while((y=y->next)->next->next);y->next=NULL;y=t

/*
**	Non-typed linked lists:
*/

#endif
