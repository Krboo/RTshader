/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alelievr <alelievr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/19 14:02:21 by alelievr          #+#    #+#             */
/*   Updated: 2017/05/03 20:39:23 by yalaouf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
# include <stdint.h>
# include "nyancat.h"
# include "term_strings.h"
# include <string.h>
# define BUFF_SIZE		4096
# define ABS(x)			(x < 0) ? -x : x
# define FT_DEBUG		ft_printf("Debug:%s:%d\n",__FILE__,__LINE__)
# define BIT_ON(x, y)	(x = x | (1 << y))
# define BIT_OFF(x, y)	(x &= ~(1 << y))
# define BIT_TEST(x, y)	(((x & (1 << y)) == 0) ? 0 : 1)
# define LOG10_E		2.718281828
# define MAX_CHAR_BUFF	0x7FF98C
# define MAX_INT_BUFF	0x1FFE63
# define HIMAGIC		0x8080808080808080lu
# define LOMAGIC		0x0101010101010101lu
# define LONGCHR_NULL(x)	(((x - LOMAGIC) & HIMAGIC) != 0)
# define LONGCHR(l, b) (((((l ^ b) - LOMAGIC) & ~(l ^ b)) & (LOMAGIC << 7))!=0)

/*
** color
*/
# define C_BLACK "\033[30m"
# define C_RED "\033[31m"
# define C_GREEN "\033[32m"
# define C_YELLOW "\033[33m"
# define C_BLUE "\033[34m"
# define C_PURPLE "\033[35m"
# define C_CYAN "\033[36m"
# define C_WHITE "\033[37m"
# define C_END "\033[0m"

/*
** color bold
*/
# define C_BLACK_B "\033[30;1m"
# define C_RED_B "\033[31;1m"
# define C_GREEN_B "\033[32;1m"
# define C_YELLOW_B "\033[33;1m"
# define C_BLUE_B "\033[34;1m"
# define C_PURPLE_B "\033[35;1m"
# define C_CYAN_B "\033[36;1m"
# define C_WHITE_B "\033[37;1m"

/*
** color underline
*/
# define C_BLACK_U "\033[30;4m"
# define C_RED_U "\033[31;4m"
# define C_GREEN_U "\033[32;4m"
# define C_YELLOW_U "\033[33;4m"
# define C_BLUE_U "\033[34;4m"
# define C_PURPLE_U "\033[35;4m"
# define C_CYAN_U "\033[36;4m"
# define C_WHITE_U "\033[37;4m"

/*
** color background
*/
# define C_BLACK_BK "\033[40m"
# define C_RED_BK "\033[41m"
# define C_GREEN_BK "\033[42m"
# define C_YELLOW_BK "\033[43m"
# define C_ULUE_BK "\033[44m"
# define C_PURPLE_BK "\033[45m"
# define C_CYAN_BK "\033[46m"
# define C_WHITE_BK "\033[47m"

/*
** Color operations:
*/
# define BLUE(x)		(x & 0x0000FF)
# define GREEN(x)		((x >> 8) & 0x0000FF)
# define RED(x)			((x >> 16) & 0x0000FF)

# define RGB(r, g, b)	(((b) << 0) | ((g) << 8) | ((r) << 16))
# define RGBG(g)		((g << 0) | (g << 8) | (g << 16))

# define DELBLUE(x)		(x & ~0x0000FF)
# define DELGREEN(x)	(x & ~0x00FF00)
# define DELRED(x)		(x & ~0xFF0000)

# define GRAY(x)		RGBG(((BLUE(x) + GREEN(x) + RED(x)) / 3))

# define INCRED(x, i)	x = (RGB((RED(x) + i), GREEN(x), BLUE(x)))
# define INCGREEN(x, i)	x = (RGB(RED(x), (GREEN(x) + i), BLUE(x)))
# define INCBLUE(x, i)	x = (RGB(RED(x), GREEN(x), (BLUE(x) + i)))

# define FT_ARGS(...)	__VA_ARGS__
# define INIT(x, y, z)		x y = z
# define IINIT(x, y, ...) x y = __VA_ARGS__
# define IFRET__(x, y)	if (x) return (y)
# define EIFRET__(x, y)	else if (x) return (y)
# define ERET__(y)		else return (y)
# define DBA(x, y, z, w) x = y, z = w;
# define DBAO(x, y, z, w, op) x op y, z op w;
# define DBI(x, y) { x; y; }
# define _

typedef struct	s_btree
{
	void			*data;
	struct s_btree	*left;
	struct s_btree	*right;
	struct s_btree	*parent;
	int				index;
	int				ftn:32;
}				t_btree;

typedef struct	s_list
{
	void			*content;
	size_t			content_size;
	struct s_list	*next;
}				t_list;

typedef struct	s_matrix
{
	double		**m;
	int			w;
	int			h;
}				t_matrix;

typedef unsigned char		t_uchar;
typedef unsigned long		t_ulong;
typedef unsigned int		t_uint;
typedef unsigned long long	t_ulonglong;
typedef unsigned long		t_ptr;
typedef unsigned long int	t_op;

void			*ft_memset(void *b, int c, size_t len);
char			*ft_itoa(int n);
void			ft_putchar(int c);
void			ft_putchar_fd(char c, int fd);
void			ft_putendl(char const *s);
void			ft_putendl_fd(char const *s, int fd);
void			ft_putnbr(int n);
void			ft_putnbr_fd(int n, int fd);
void			ft_putstr(char const *s);
void			ft_putstr_fd(char const *s, int fd);
char			*ft_strcpy(char *dst, char const *src);
size_t			ft_strlen(char const *s);
char			**ft_strsplit(char const *s, char c);
char			**ft_strsplitstr(char const *s, char *c);
int				ft_nbr_split(char *s, char c);
void			ft_bzero(void *s, size_t n);
char			*ft_strtrim(char const *s);
char			*ft_strcut(char const *s, int n);
void			*ft_memcpy(void *dst, void const *src, size_t n);
void			*ft_memccpy(void *dst, void const *src, int c, size_t n);
void			*ft_memmove(void *dst, void const *src, size_t len);
void			*ft_memchr(void const *s, int c, size_t n);
int				ft_memcmp(void const *s1, void const *s2, size_t n);
char			*ft_strdup(char const *s1);
char			*ft_strncpy(char *dst, char const *src, size_t n);
char			*ft_strcat(char *s1, char *s2);
char			*ft_strncat(char *s1, const char *s2, size_t n);
size_t			ft_strlcat(char *dst, char const *src, size_t size);
size_t			ft_strlcpy(char *dst, const char *src, size_t size);
char			*ft_strchr(char const *s1, int c);
char			*ft_strnchr(char const *s1, int c, int n);
char			*ft_strrchr(char const *s1, int c);
char			*ft_strstr(char const *s1, char const *s2);
char			*ft_strnstr(char const *s1, char const *s2, size_t n);
int				ft_strcmp(char const *s1, char const *s2);
int				ft_strncmp(char const *s1, char const *s2, size_t n);
int				ft_atoi(const char *str);
long long int	ft_atoll(const char *str);
double			ft_atof(const char *str);
int				ft_isalpha(int c);
int				ft_isdigit(int c);
int				ft_isalnum(int c);
int				ft_isascii(int c);
int				ft_isprint(int c);
int				ft_toupper(int c);
int				ft_tolower(int c);
void			*ft_memalloc(size_t size);
void			ft_memdel(void **ap);
char			*ft_strnew(size_t size);
void			ft_strdel(char **as);
void			ft_strclr(char *s);
void			ft_striter(char *s, void (*f)(char *));
void			ft_striteri(char *s, void (*f)(unsigned int, char *));
char			*ft_strmap(char const *s, char (*f)(char));
char			*ft_strmapi(char const *s, char (*f)(unsigned int, char));
int				ft_strequ(char const *s1, char const *s2);
int				ft_strnequ(char const *s1, char const *s2, size_t n);
char			*ft_strsub(char const *s, unsigned int start, size_t len);
char			*ft_strjoin(char const *s1, char const *s2);

t_list			*ft_lstnew(void const *content, size_t content_size);
void			ft_print_list(t_list *begin_list);
void			ft_lstdelone(t_list **alst, void (*del)(void *, size_t));
void			ft_lstdel(t_list **alst, void (*del)(void *, size_t));
void			ft_lstadd(t_list **alst, t_list *new);
void			ft_lsteadd(t_list **alst, t_list *new);
void			ft_lstiter(t_list *lst, void (*f)(t_list *elem));
t_list			*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem));
int				ft_nbr_split(char *s, char c);
int				ft_strclen(char *str, char c);
t_list			*ft_lstsplit(char *s, char c);

t_btree			*btree_create_node(void *item, int index);
void			btree_apply_prefix(t_btree *root, void (*applyf)(void *));
void			btree_apply_infix(t_btree *root, void (*applyf)(void *));
void			btree_apply_suffix(t_btree *root, void (*applyf)(void *));

void			ft_putascii(unsigned char c);
void			ft_aputstr(unsigned char *str, size_t len);
int				ft_convert(char *buffer, int64_t n, int b, int maj);
char			*ft_strndup(char const *s1, unsigned int len);
void			ft_swap(int *a, int *b);
int				ft_abs(int n);
int				ft_isblank(int n);
int				ft_ispunct(int c);
int				ft_isspace(int c);
int				ft_isupper(int c);
char			*ft_memdup(char *s, unsigned int size);
char			*ft_memnew(size_t size);
char			*ft_strupcase(char *str);
char			*ft_strlowcase(char *str);
char			*ft_strrev(char *s);
char			*ft_strtrimc(char const *s, char c);
char			*ft_strcapitalize(char *str);
void			ft_ptrswap(void *p1, void *p2);
void			ft_memswap(void *d1, void *d2, size_t size);
int				ft_firstocc(char *s, char c);
int				ft_lastocc(char *s, char c);
void			ft_putdouble(double d);
void			ft_putlong(long l);
size_t			ft_intlen(long long n);
int				get_next_line(int fd, char **line);
void			ft_putnbrpos(int nb, int align);
void			ft_putstrpos(char *s, int pos);
int				rgb(int r, int g, int b);
int				aliase(int c1, int c2);
void			ft_putlong_fd(long l, int fd);
void			m_error(void) __attribute__((noreturn));
void			error(char *str) __attribute__((noreturn));
void			ft_putstr_color(char *str, int color);
void			ft_putnbr_color(int nb, int color);
void			ft_putchar_color(char c, int color);
void			*ft_memmem(void *addr, char *str, size_t len);
int64_t			ft_deconvert(char *n, int b);
int				ret_base(unsigned char c);
int64_t			ft_ndeconvert(char *n, int b, int len);
void			ft_putstrcpos(char *s, char c, int align);
void			ft_putstrcpos_fd(char *s, char c, int align, int fd);
char			*ft_shr(char *str, int n);
char			*ft_shl(char *str, int n);
int				ft_nmatch(char *s1, char *s2);
int				ft_strmatch(char *s1, char *s2);
int				ft_perror(char *error);
const char		*ft_strerror(int err);
int				ft_nbrocc(char *str, char c);
int				ft_nnbrocc(char *str, char c, int len);
char			*ft_strtr(char *str, char src, char dst);
char			*ft_strtrstr(char *dst, char *src, char *to_tr, char *tr);
int				ft_memocc(void *mem, char *occ, int len);
int				ft_getocc(char *str, char c, int n);
int				ft_strnmatch(char *s1, char *s2);
void			ft_exit(char *f, ...) __attribute__((noreturn));

/*
** Math functions:
*/

long			ft_factorial(int nb);
int64_t			ft_pow(int64_t n, int pow);
double			ft_sqrt(int nb);
int				ft_intsize(int a);
_Bool			cmp_float(double f1, double f2);

#endif
