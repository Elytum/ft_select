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

static void	ft_enter2(t_env *e, char *buffer)
{
	t_str	*ptr;

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
		write(1, buffer, ft_strlen(buffer));
		free(buffer);
	}
	close(sing_tty());
	exit(0);
}

void		ft_enter(t_env *e, char *inputs)
{
	if (!(inputs[0] == 10 && inputs[1] == 0 && inputs[2] == 0 &&
		inputs[3] == 0 && inputs[4] == 0 && inputs[5] == 0))
		return ;
	write(sing_tty(), tgoto(tgetstr("cm", NULL), 0, 0),
		ft_strlen(tgoto(tgetstr("cm", NULL), 0, 0)));
	write(sing_tty(), tgetstr("cd", NULL), 3);
	write(sing_tty(), tgetstr("ve", NULL), 12);
	ft_enter2(e, NULL);
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
