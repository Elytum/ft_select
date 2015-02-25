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

void		ft_enter(t_env *e, char *inputs)
{
	t_str	*ptr;
	char	*buffer;

	if (!(inputs[0] == 10 && inputs[1] == 0 && inputs[2] == 0 &&
		inputs[3] == 0 && inputs[4] == 0 && inputs[5] == 0))
		return ;
	tputs(tgoto(tgetstr("cm", (char **)(&e->p->buf)), 0, 0), 1, ft_putc);
	tputs(tgetstr("cd", (char **)(&e->p->buf)), 1, ft_putc);
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
	buffer = ft_strjoinf1(&buffer, "\n");
	buffer = ft_strjoinf1(&buffer, tgetstr("ve", (char **)(&e->p->buf)));
	tputs(buffer, 1, ft_putc);
	free(buffer);
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
}

void		ft_arrows(t_env *e, char *inputs)
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

void		ft_putselect(t_env *e)
{
	t_str	*pos;
	char	*b;

	b = ft_strdup(tgoto(tgetstr("cm", (char **)(&e->p->buf)), 0, 0));
	b = ft_strjoinf1(&b, tgetstr("cd", (char **)(&e->p->buf)));
	pos = e->lst;
	while (pos)
	{
		if (pos->flags & 0b00000001)
			b = ft_strjoinf1(&b, tgetstr("us", (char **)(&e->p->buf)));
		if (pos->flags & 0b00000010)
			b = ft_strjoinf1(&b, tgetstr("mr", (char **)(&e->p->buf)));
		b = ft_strjoinf1(&b, pos->str);
		b = ft_strjoinf1(&b, "\n");
		b = ft_strjoinf1(&b, tgetstr("me", (char **)(&e->p->buf)));
		pos = pos->next;
	}
	b = ft_strjoinf1(&b, tgoto(tgetstr("cm", \
						(char **)(&e->p->buf)), e->x, e->y));
	tputs(b, 1, ft_putc);
	free(b);
}
