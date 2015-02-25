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

#include <stdio.h>

t_env		*ft_get_env(t_env **e)
{
	static	t_env *save = NULL;

	if (e)
		save = *e;
	return (save);
}

void		ft_update_max(int sig_num)
{
	t_env	*e;

	e = ft_get_env(NULL);
	dprintf(1, "Past height = %i, Past width = %i\n", e->height, e->width);
	e->height = tgetnum ("li");
	e->width = tgetnum ("co");
	dprintf(1, "New height = %i, new width = %i\n", tgetnum ("li"), tgetnum ("co"));
	(void)sig_num;
}

void		ft_ctrl_c(int sig_num)
{
	t_env	*e;

	e = ft_get_env(NULL);
	tputs(tgetstr("ve", (char **)(&e->p->buf)), 1, ft_putc);
	tputs(tgetstr("me", (char **)(&e->p->buf)), 1, ft_putc);
	(void)sig_num;
	exit (0);
}

void		ft_init_signals(t_env *e)
{
	ft_get_env(&e);
	e->height = tgetnum ("li");
	e->width = tgetnum ("co");
	signal (SIGWINCH, ft_update_max);
	signal (SIGINT, ft_ctrl_c);
}