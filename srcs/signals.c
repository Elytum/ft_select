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

t_env					*ft_get_env(t_env **e)
{
	static				t_env *save = NULL;

	if (e)
		save = *e;
	return (save);
}

void					ft_update_max(int sig_num)
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

void					ft_ctrl_c(int sig_num)
{
	struct termios		*p;

	write(sing_tty(), tgoto(tgetstr("cm", NULL), 0, 0),
		ft_strlen(tgoto(tgetstr("cm", NULL), 0, 0)));
	write(sing_tty(), tgetstr("cd", NULL), 3);
	write(sing_tty(), tgetstr("ve", NULL), 12);
	close(sing_tty());
	p = sing_oldterm(NULL);
	tcsetattr(0, 0, p);
	exit(sig_num);
}

int						sing_tty(void)
{
	static int			fd = -1;

	if (fd == -1)
		fd = open("/dev/tty", O_WRONLY);
	return (fd);
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
	signal(SIGSTOP, &ft_ctrl_c);
	signal(SIGCONT, &ft_ctrl_c);
	signal(SIGSEGV, &ft_ctrl_c);
	signal(SIGQUIT, &ft_ctrl_c);
	signal(SIGFPE, &ft_ctrl_c);
	signal(SIGALRM, &ft_ctrl_c);
	signal(SIGKILL, &ft_ctrl_c);
	signal(SIGABRT, &ft_ctrl_c);
	signal(SIGUSR1, &ft_ctrl_c);
	signal(SIGUSR2, &ft_ctrl_c);
}
