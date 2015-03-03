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

	if (!((inputs[0] == 27 && inputs[1] == 91) && (inputs[2] == 67 || inputs[2] == 68)))
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