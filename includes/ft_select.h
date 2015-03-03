/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_select.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achazal <achazal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/18 02:14:06 by achazal           #+#    #+#             */
/*   Updated: 2015/02/18 02:14:08 by achazal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SELECT_H
# define FT_SELECT_H
# include <signal.h>
# include <termios.h>
# include <termcap.h>
# include <curses.h>

# define TERM_BUF 4000

typedef struct		s_params
{
	char			**av;
	int				ac;
	char			*v_term;
	char			buf[2048];
	struct termios	term;
	struct termios	*oldterm;
	char			r_char[4];
	int				print;
	tcflag_t		old_term;
	int				c_pos_x;
	int				c_pos_y;
	int				l_count;
	int				col_count;
	int				max_size;
}					t_params;

typedef struct		s_int
{
	short int		move;
	struct s_int	*next;
	struct s_int	*past;
}					t_int;

typedef struct		s_str
{
	char			*str;
	int				flags;
	struct s_str	*next;
	struct s_str	*past;
}					t_str;

typedef struct		s_env
{
	char			*input;
	t_params		*p;
	t_str			*lst;
	t_str			*ptr;
	t_int			*histo;
	int				tty;
	int				width;
	int				height;
	int				maxx;
	int				maxy;
	int				x;
	int				y;
	int				put;
	size_t			sizeofcol;
}					t_env;

void				ft_putstr(char *str);
int					ft_strlen(char *str);
char				*ft_strdup(char *str);
void				*ft_memalloc(size_t size);
int					ft_putc(int c);
t_params			*ft_get_params(void);
void				ft_bzero(void *s, size_t n);
char				*ft_strjoin(char *s1, char *s2);
char				*ft_strjoinf1(char **s1, char *s2);
char				*ft_strjoinf2(char *s1, char **s2);

void				ft_putselect(t_env *e);
void				ft_delete(t_env *e, char *inputs);
void				ft_up_down(t_env *e, char *inputs);
void				ft_left_right(t_env *e, char *inputs);
void				ft_select(t_env *e, char *inputs);
void				ft_enter(t_env *e, char *inputs);
void				ft_echap(t_env *e, char *inputs);

void				ft_init_signals(t_env *e);

struct termios		*sing_oldterm(struct termios *term);
int					sing_tty(void);

#endif
