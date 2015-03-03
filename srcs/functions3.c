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
#include <stdio.h>
#include <sys/ioctl.h>

void			ft_setposition(t_env *e, int x, int y)
{
	int			pos;
	int			maxcol;
	t_str		*ptr;

	maxcol = e->maxy / e->height + (e->maxy % e->height > 0);
	if (e->height >= e->maxy)
		return ;
	while (x <= 0)
		x += maxcol;
	while (x >= maxcol)
		x -= maxcol;
	if (x == maxcol - 1 && y >= e->maxy % e->height)
		x--;
	pos = (e->height * x + y);
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
	else
		ft_setposition(e, 0, y);
}

void			ft_left_right(t_env *e, char *inputs)
{
	t_str		*ptr;
	// int			max;
	// int			v;
	int			x;
	int			y;

	// dprintf(sing_tty(), "%i %i %i\n", inputs[0], inputs[1], inputs[2]);
//	sleep(2);
	if (!((inputs[0] == 27 && inputs[1] == 91) && (inputs[2] == 67 || inputs[2] == 68)))
		return ;
	// left 68
	// right 67

	x = 0;
	y = 0;
	ptr = e->lst;
	while (ptr)
	{
		if (ptr->flags & 0b00000001)
		{
			if (inputs[2] == 68)
				ft_setposition(e, x - 1, y);
			else
				ft_setposition(e, x + 1, y);
			ptr->flags &= ~0b00000001;
			return ;
		}
		y++;
		if (y >= e->height)
		{
			y = 0;
			x++;
		}
		ptr = ptr->next;
	}
	// dprintf(sing_tty(), "%i %i %i\n", inputs[0], inputs[1], inputs[2]);
	// sleep(2);
}