/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achazal <achazal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/18 02:14:06 by achazal           #+#    #+#             */
/*   Updated: 2015/02/18 02:14:08 by achazal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_select.h"
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

void		ft_do_delete(t_env *e)
{
	t_str	*tmp;

	if (e->ptr->past && e->ptr->next)
	{
		tmp = e->ptr->next;
		(e->ptr->past)->next = e->ptr->next;
		(e->ptr->next)->past = e->ptr->past;
	}
	else if (e->ptr->past)
	{
		tmp = e->ptr->past;
		tmp->next = NULL;
	}
	else
	{
		tmp = e->ptr->next;
		tmp->past = NULL;
		e->lst = tmp;
	}
	tmp->flags |= 0b00000001;
	free(e->ptr->str);
	free(e->ptr);
	e->ptr = tmp;
}

void		ft_delete(t_env *e, char *inputs)
{
	if (!(inputs[0] == 127 && inputs[1] == 0 && inputs[2] == 0 &&
		inputs[3] == 0 && inputs[5] == 0 && inputs[5] == 0) &&
		!(inputs[0] == 27 && inputs[1] == 91 && inputs[2] == 51 &&
		inputs[3] == 126 && inputs[5] == 0 && inputs[5] == 0))
		return ;
	e->put = 1;
	if (!(e->ptr->past || e->ptr->next))
	{
		write(sing_tty(), tgetstr("ve", NULL), 12);
		close(sing_tty());
		exit(0);
	}
	ft_do_delete(e);
}

void		ft_echap(t_env *e, char *inputs)
{
	if (!(inputs[0] == 27 && inputs[1] == 0 && inputs[2] == 0))
		return ;
	write(sing_tty(), tgetstr("ve", NULL), 12);
	close(sing_tty());
	(void)e;
	exit (0);
}
