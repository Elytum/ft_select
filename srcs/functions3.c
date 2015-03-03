/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions3.c                                       :+:      :+:    :+:   */
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

static void		ft_setposition(t_env *e, int x, int y)
{
	int			pos;
	int			maxcol;
	int			tmpx;
	t_str		*ptr;

	tmpx = x;
	maxcol = e->maxy / e->height + (e->maxy % e->height > 0);
	while (tmpx <= 0)
		tmpx += maxcol;
	while (tmpx >= maxcol)
		tmpx -= maxcol;
	if (tmpx == maxcol - 1 && y >= e->maxy % e->height)
		tmpx = (x == -1) ? tmpx - 1 : 0;
	pos = (e->height * tmpx + y);
	ptr = e->lst;
	while (ptr && pos)
	{
		pos--;
		ptr = ptr->next;
	}
	if (!pos && !(ptr->flags & 0b00000001))
	{
		ptr->flags |= 0b00000001;
		e->ptr = ptr;
	}
}

void			ft_left_right(t_env *e, char *inputs)
{
	t_str		*ptr;
	int			x;
	int			y;

	if (!((inputs[0] == 27 && inputs[1] == 91) &&
		(inputs[2] == 67 || inputs[2] == 68)))
		return ;
	x = 0;
	y = 0;
	ptr = e->lst;
	while (ptr)
	{
		if (ptr->flags & 0b00000001)
		{
			ptr->flags &= ~0b00000001;
			if (inputs[2] == 68)
				ft_setposition(e, x - 1, y);
			else
				ft_setposition(e, x + 1, y);
			return ;
		}
		if (++y >= e->height && ++x)
			y = 0;
		ptr = ptr->next;
	}
}

static void		ft_do_delete(t_env *e)
{
	t_str		*tmp;

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
	e->maxy--;
}

void			ft_delete(t_env *e, char *inputs)
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

void			ft_echap(t_env *e, char *inputs)
{
	if (!(inputs[0] == 27 && inputs[1] == 0 && inputs[2] == 0))
		return ;
	write(sing_tty(), tgetstr("ve", NULL), 12);
	close(sing_tty());
	(void)e;
	exit (0);
}
