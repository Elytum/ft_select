/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   params.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achazal <achazal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/18 02:14:06 by achazal           #+#    #+#             */
/*   Updated: 2015/02/18 02:14:08 by achazal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_select.h"
#include <stdlib.h>
#include <fcntl.h>

t_env					*ft_get_env(t_env **e)
{
	static				t_env *save = NULL;

	if (e)
		save = *e;
	return (save);
}

int						sing_tty(void)
{
	static int			fd = -1;

	if (fd == -1)
		fd = open("/dev/tty", O_WRONLY);
	return (fd);
}

BYPASS					*sing_oldterm(BYPASS *term)
{
	static BYPASS		*old;

	if (term != NULL)
		old = term;
	return (old);
}

BYPASS					*sing_newterm(BYPASS *term)
{
	static BYPASS			*new;

	if (term != NULL)
		new = term;
	return (new);
}

t_params				*ft_get_params(void)
{
	t_params			*p;

	if (!(p = (t_params *)ft_memalloc(sizeof(t_params))))
		return (NULL);
	p->c_pos_x = 0;
	p->c_pos_y = 0;
	p->print = 0;
	if (tgetent(p->buf, p->v_term) < 1)
		return (NULL);
	tcgetattr(0, &p->term);
	p->term.c_lflag &= ~(ICANON);
	p->term.c_lflag &= ~(ECHO);
	p->term.c_cc[VMIN] = 1;
	p->term.c_cc[VTIME] = 0;
	tcgetattr(0, p->oldterm);
	sing_oldterm(p->oldterm);
	if (tcsetattr(0, TCSADRAIN, &p->term) == -1)
		return (NULL);
	p->max_size = 1;
	p->col_count = 1;
	sing_newterm(&(p->term));
	return (p);
}
