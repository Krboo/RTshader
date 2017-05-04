/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_std.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alelievr <alelievr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/28 16:13:04 by alelievr          #+#    #+#             */
/*   Updated: 2015/03/29 16:29:24 by alelievr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_STD_H
# define FT_STD_H

# include "libft.h"
# include <stdlib.h>
# include <stdint.h>

typedef struct	s_str
{
	char			buff[0xF00];
	char			*null;
	struct s_str	*tbuff;
	struct s_str	*parent;
	int				tablen;
	int				freet;
	char			*duped;
	int				freed;
	int				strlen;
	struct s_str	(*set)(struct s_str *, char *);
	struct s_str	(*cat)(struct s_str *, char *);
	struct s_str	(*icat)(struct s_str *, int, int);
	struct s_str	*(*split)(struct s_str *, char *);
	struct s_str	(*tr)(struct s_str *, char, char);
	int				(*conv)(struct s_str *, int);
	int				(*len)(struct s_str *);
	int				(*tlen)(struct s_str *);
	int				(*atoi)(struct s_str *);
	int				(*cmp)(struct s_str *, char *);
	void			(*disp)(struct s_str *);
	void			(*tdisp)(struct s_str *);
	char			*(*dup)(struct s_str *);
	char			*(*ndup)(struct s_str *, int);
	char			**(*tdup)(struct s_str *);
	char			*(*val)(struct s_str *);
	char			*(*str)(struct s_str *, char *);
	char			*(*next_word)(struct s_str *);
	void			(*stdfree)(struct s_str *);
}				t_str;

t_str			std_init(t_str *s);

t_str			set(t_str *s, char *str);
t_str			cat(t_str *s, char *cat);
t_str			icat(t_str *s, int i, int b);
t_str			*split(t_str *s, char *split);
t_str			stdtr(t_str *s, char c, char sub);
int				stdconv(t_str *s, int i);
int				stdlen(t_str *s);
int				tlen(t_str *s);
int				stdatoi(t_str *s);
int				stdcmp(t_str *s, char *str);
void			disp(t_str *s);
void			tdisp(t_str *s);
char			*sdup(t_str *s);
char			*ndup(t_str *s, int i);
char			**tdup(t_str *s);
char			*val(t_str *s);
void			stdfree(t_str *s);
char			*stdstrstr(t_str *s, char *str);
char			*next_word(t_str *s);

#endif
