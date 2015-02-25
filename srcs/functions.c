/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions.c                                        :+:      :+:    :+:   */
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
#include <unistd.h>
#include <stdio.h>

void		ft_enter(t_env *e, char *inputs)
{
	t_str	*ptr;
	char	*buffer;

	if (!(inputs[0] == 10 && inputs[1] == 0 && inputs[2] == 0 &&
		inputs[3] == 0 && inputs[4] == 0 && inputs[5] == 0))
		return ;
	write(sing_tty(), tgoto(tgetstr("cm", NULL), 0, 0), ft_strlen(tgoto(tgetstr("cm", NULL), 0, 0)));
	write(sing_tty(), tgetstr("cd", NULL), 3);
	write(sing_tty(), tgetstr("ve", NULL), 12);
	buffer = NULL;
	ptr = e->lst;
	while (ptr)
	{
		if (ptr->flags & 0b00000010)
		{
			if (buffer)
				buffer = ft_strjoinf1(&buffer, " ");
			buffer = ft_strjoinf1(&buffer, ptr->str);
		}
		ptr = ptr->next;
	}
	if (buffer)
	{
		buffer = ft_strjoinf1(&buffer, "\n");
		write(sing_tty(), buffer, ft_strlen(buffer));
		free(buffer);
	}
	close(sing_tty());
	exit(0);
}

void		ft_select(t_env *e, char *inputs)
{
	if (!(inputs[0] == 32 && inputs[1] == 0 && inputs[2] == 0 &&
		inputs[3] == 0 && inputs[4] == 0 && inputs[5] == 0))
		return ;
	e->put = 1;
	if (e->ptr->flags & 0b00000010)
		e->ptr->flags &= ~0b00000010;
	else
		e->ptr->flags |= 0b00000010;
	e->ptr->flags &= ~0b00000001;
	if (e->ptr->next)
		e->ptr = e->ptr->next;
	else
		e->ptr = e->lst;
	e->ptr->flags |= 0b00000001;
}

void		ft_up_down(t_env *e, char *inputs)
{
	if (!((inputs[0] == 27 && inputs[1] == 91) && (inputs[2] == 65 ||
		inputs[2] == 66) && inputs[3] == 0 && inputs[4] == 0 &&
		inputs[5] == 0))
		return ;
	e->put = 1;
	e->ptr->flags &= ~0b00000001;
	if (inputs[2] == 65)
	{
		if (e->ptr->past)
			e->ptr = e->ptr->past;
		else
		{
			e->ptr = e->lst;
			while (e->ptr->next)
				e->ptr = e->ptr->next;
		}
	}
	else
	{
		if (e->ptr->next)
			e->ptr = e->ptr->next;
		else
			e->ptr = e->lst;
	}
	e->ptr->flags |= 0b00000001;
}
#include <unistd.h>
#include <stdio.h>

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

void		ft_putselect(t_env *e)
{
	t_str	*pos;
	char	*b;

	if (e->width <= e->maxx)
	{
		write(sing_tty(), "Screen size too little\n", 24);
		return ;
	}
	if (e->height <= e->maxy)
	{
		ft_put_col(e);
		return ;
	}
	b = ft_strdup(tgoto(tgetstr("cm", NULL), 0, 0));
	b = ft_strjoinf1(&b, tgetstr("cd", NULL));
	pos = e->lst;
	while (pos)
	{
		if (pos->flags & 0b00000001)
			b = ft_strjoinf1(&b, tgetstr("us", NULL));
		if (pos->flags & 0b00000010)
			b = ft_strjoinf1(&b, tgetstr("mr", NULL));
		b = ft_strjoinf1(&b, pos->str);
		b = ft_strjoinf1(&b, "\n");
		b = ft_strjoinf1(&b, tgetstr("me", NULL));
		pos = pos->next;
	}
	b = ft_strjoinf1(&b, tgoto(tgetstr("cm", \
						NULL), e->x, e->y));
	write(sing_tty(), b, ft_strlen(b));
	free(b);
}
