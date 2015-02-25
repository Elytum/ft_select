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

#include "../includes/ft_select.h"
#include <stdlib.h>

void		ft_do_delete(t_env *e)
{
	t_str	*tmp;

	if (e->ptr->past && e->ptr->next)
	{
		tmp = e->ptr->past;
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
		tputs(tgetstr("ve", (char **)(&e->p->buf)), 1, ft_putc);
		exit (0);
	}
	ft_do_delete(e);
}
