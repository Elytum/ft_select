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

#include <stdio.h>

t_env		*ft_get_env(t_env **e)
{
	static	t_env *save = NULL;

	if (e)
		save = *e;
	return (save);
}
 #include <sys/ioctl.h>
void		ft_update_max(int sig_num)
{
	t_env	*e;
	struct winsize		win;
	// t_select			*tmp;

	e = ft_get_env(NULL);
	// dprintf(1, "Past height = %i, Past width = %i\n", e->height, e->width);
	ioctl(0, TIOCGWINSZ, &win);
	e->width = (int)win.ws_col;
	e->height = (int)win.ws_row;
	write(sing_tty(), tgetstr("cl", NULL), ft_strlen(tgetstr("cl", NULL)));
	ft_putselect(e);
	// dprintf(sing_tty(), "New height = %i, new width = %i\n", e->width, e->height);
	(void)sig_num;
}

void		ft_ctrl_c(int sig_num)
{
	char	*str;
	t_env	*e;

	e = ft_get_env(NULL);

	str = tgetstr("ve", NULL);
	write(sing_tty(), str, ft_strlen(str));
	str = tgetstr("me", NULL);
	write(sing_tty(), str, ft_strlen(str));
	close(sing_tty());
	(void)sig_num;
	exit (0);
}

int					sing_tty(void)
{
	static int		fd = -1;

	if (fd == -1)
		fd = open("/dev/tty", O_WRONLY);
	return (fd);
}

void				ft_signal(void)
{
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

void		ft_init_signals(t_env *e)
{
// `	static void		se_sigredim(void)
// {
	// struct winsize		win;
	// t_select			*tmp;

	// ioctl(0, TIOCGWINSZ, &win);
	// tmp = sing_select(NULL);
	// e->width = (int)win.ws_row;
	// e->height = (int)win.ws_col;
	// tputs(tmp->cl_str, 1, tputs_putchar);
	// se_print_list(tmp);
// }

	ft_get_env(&e);
	e->height = tgetnum ("li");
	e->width = tgetnum ("co");
	ft_signal();
	signal (SIGWINCH, &ft_update_max);
	signal (SIGINT, &ft_ctrl_c);
}