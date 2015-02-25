/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sh1.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-bonn <ade-bonn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/23 11:55:51 by ade-bonn          #+#    #+#             */
/*   Updated: 2015/02/06 14:17:34 by ade-bonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SH1_H
# define FT_SH1_H
# include <sys/param.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <signal.h>
# include <pwd.h>
# include <termios.h>
# include <termcap.h>
# include <signal.h>
# include <curses.h>
# include <term.h>
# include <errno.h>
# include <curses.h>

# include <stdio.h>

typedef struct		s_params
{
	char			**av;
	int				ac;
	char			*v_term;
	char			buf[2048];
	struct termios	term;
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
	int				width;
	int				height;
	int				x;
	int				y;
	int				put;
}					t_env;

void				ft_putstr(char *str);
int					ft_strlen(char *str);
char				*ft_strdup(char *str);
void				*ft_memalloc(size_t size);
int					ft_putc(int c);
t_params			*ft_get_params(void);
void				ft_bzero(void *s, size_t n);

#endif


