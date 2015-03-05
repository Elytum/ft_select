/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achazal <achazal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/18 02:14:06 by achazal           #+#    #+#             */
/*   Updated: 2015/02/18 02:14:08 by achazal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_select.h"
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <stdio.h>

static void				ft_update_max(int sig_num)
{
	t_env				*e;
	struct winsize		win;

	e = ft_get_env(NULL);
	ioctl(0, TIOCGWINSZ, &win);
	e->width = (int)win.ws_col;
	e->height = (int)win.ws_row;
	write(sing_tty(), tgetstr("cl", NULL), ft_strlen(tgetstr("cl", NULL)));
	ft_putselect(e);
	(void)sig_num;
}

static void				ft_ctrl_c(int sig_num)
{
	char				*str;

	str = tgoto(tgetstr("cm", NULL), 0, 0);
	write(sing_tty(), str, ft_strlen(str));
	write(sing_tty(), tgetstr("cd", NULL), 3);
	write(sing_tty(), tgetstr("ve", NULL), 12);
	close(sing_tty());
	tcsetattr(0, 0, sing_oldterm(NULL));
	exit(sig_num);
}

static void				h_sigstop(int sig_num)
{
	char				*str;

	str = tgoto(tgetstr("cm", NULL), 0, 0);
	write(sing_tty(), str, ft_strlen(str));
	str = tgetstr("cd", NULL);
	write(sing_tty(), str, ft_strlen(str));
	str = tgetstr("ve", NULL);
	write(sing_tty(), str, ft_strlen(str));
	str = tgetstr("me", NULL);
	write(sing_tty(), str, ft_strlen(str));
	tcsetattr(0, TCSANOW, sing_oldterm(NULL));
	close(sing_tty());
	(void)sig_num;
}

static void				h_sigcont(int sig_num)
{
	tcsetattr(0, 0, sing_newterm(NULL));
	sing_tty();
	ft_loop(ft_get_env(NULL));
	(void)sig_num;
}

void					ft_init_signals(t_env *e)
{
	e->height = tgetnum ("li");
	e->width = tgetnum ("co");
	ft_get_env(&e);
	signal(SIGWINCH, &ft_update_max);
	signal(SIGINT, &ft_ctrl_c);
	signal(SIGINT, &ft_ctrl_c);
	signal(SIGHUP, &ft_ctrl_c);
	signal(SIGTERM, &ft_ctrl_c);
	signal(SIGSTOP, &h_sigstop);
	signal(SIGSTOP, &h_sigstop);
	signal(SIGCONT, &h_sigcont);
	signal(SIGSEGV, &ft_ctrl_c);
	signal(SIGQUIT, &ft_ctrl_c);
	signal(SIGFPE, &ft_ctrl_c);
	signal(SIGALRM, &ft_ctrl_c);
	signal(SIGKILL, &ft_ctrl_c);
	signal(SIGABRT, &ft_ctrl_c);
	signal(SIGUSR1, &ft_ctrl_c);
	signal(SIGUSR2, &ft_ctrl_c);
}
