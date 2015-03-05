/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions4.c                                       :+:      :+:    :+:   */
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

static void	ft_put_col2(t_env *e, t_str *ptr, int max)
{
	int		x;
	int		y;

	y = 0;
	x = 0;
	while (ptr)
	{
		write(sing_tty(0), tgoto(tgetstr("cm", NULL), x * max, y),
			ft_strlen(tgoto(tgetstr("cm", NULL), x * max, y)));
		if (ptr->flags & 0b00000001)
			write(sing_tty(0), tgetstr("us", NULL),
				ft_strlen(tgetstr("us", NULL)));
		if (ptr->flags & 0b00000010)
			write(sing_tty(0), tgetstr("mr", NULL),
				ft_strlen(tgetstr("mr", NULL)));
		write(sing_tty(0), ptr->str, ft_strlen(ptr->str));
		write(sing_tty(0), tgetstr("me", NULL), ft_strlen(tgetstr("me", NULL)));
		y++;
		if (y >= e->height)
		{
			y = 0;
			x++;
		}
		ptr = ptr->next;
	}
}

void		ft_put_col(t_env *e)
{
	t_str	*ptr;
	int		max;
	int		v;

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
	write(sing_tty(0), tgoto(tgetstr("cm", NULL), 0, 0),
		ft_strlen(tgoto(tgetstr("cm", NULL), 0, 0)));
	write(sing_tty(0), tgetstr("cd", NULL), ft_strlen(tgetstr("cd", NULL)));
	if ((e->width / max) * e->height < e->maxy)
	{
		write (sing_tty(0), "Screen size too little\n", 24);
		return ;
	}
	ft_put_col2(e, e->lst, max);
}

static void	ft_putselect2(t_env *e, t_str *pos, char *b)
{
	b = ft_strdup(tgoto(tgetstr("cm", NULL), 0, 0));
	b = ft_strjoinf1(&b, tgetstr("cd", NULL));
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
	write(sing_tty(0), b, ft_strlen(b));
	free(b);
}

void		ft_putselect(t_env *e)
{
	if (e->width <= e->maxx)
	{
		write(sing_tty(0), "Screen size too little\n", 24);
		return ;
	}
	if (e->height <= e->maxy)
	{
		ft_put_col(e);
		return ;
	}
	ft_putselect2(e, e->lst, NULL);
}
