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

/*
void		ft_put_col(t_env *e)
{
	t_str	*ptr;
	int		max;
	int		v;
	int 	x;
	int		y;

	max = 0;
	ptr = e->lst;
	while (ptr)
	{
		v = ft_strlen(ptr->str);
		if (max < v)
			max = v;
		ptr = ptr->next;
	}
	max += 2;
	write(sing_tty(), tgoto(tgetstr("cm", NULL), 0, 0), ft_strlen(tgoto(tgetstr("cm", NULL), 0, 0)));
	write(sing_tty(), tgetstr("cd", NULL), ft_strlen(tgetstr("cd", NULL)));
	if ((e->width / max) * e->height < e->maxy)
	{
		write (sing_tty(), "Screen size too little\n", 24);
		return ;
	}
	y = 0;
	x = 0;
	ptr = e->lst;
	while (ptr)
	{
		write(sing_tty(), tgoto(tgetstr("cm", NULL), x * max, y) , ft_strlen(tgoto(tgetstr("cm", NULL), x * max, y)));
		if (ptr->flags & 0b00000001)
			write(sing_tty(), tgetstr("us", NULL), ft_strlen(tgetstr("us", NULL)));
		if (ptr->flags & 0b00000010)
			write(sing_tty(), tgetstr("mr", NULL), ft_strlen(tgetstr("mr", NULL)));
		write(sing_tty(), ptr->str, ft_strlen(ptr->str));
		write(sing_tty(), tgetstr("me", NULL), ft_strlen(tgetstr("me", NULL)));
		y++;
		if (y >= e->height)
		{
			y = 0;
			x++;
		}
		ptr = ptr->next;
	}
}
*/
void			ft_setposition(t_env *e, int x, int y)
{
	int			pos;
	int			maxcol;
	t_str		*ptr;

	maxcol = e->maxy / e->height + (e->maxy % e->height > 0);
	ptr = e->lst;
	if (e->height >= e->maxy)
		return ;
	if (x < 0)
		x += maxcol;
	pos = x * y;
	if (pos > e->height)
		pos = 0;
	while (pos)
//		pos++;
		//Quand ptr est set
	ptr->flags |= 0b00000001;


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
		}
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