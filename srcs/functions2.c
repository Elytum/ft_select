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

void		ft_reset(t_env *e, char *inputs)
{
	t_str	*ptr;

	if (!((inputs[0] == 'r' && inputs[1] == 0) &&
		(inputs[2] == 0)))
		return ;
	ptr = e->lst;
	while (ptr)
	{
		ptr->flags &= ~0b00000001;
		ptr->flags &= ~0b00000010;
		ptr = ptr->next;
	}
	e->lst->flags |= 0b00000001;
	e->ptr = e->lst;
}

void		ft_reverse(t_env *e, char *inputs)
{
	t_str	*ptr;

	if (!((inputs[0] == 'i' && inputs[1] == 0) &&
		(inputs[2] == 0)))
		return ;
	ptr = e->lst;
	while (ptr)
	{
		if (ptr->flags & 0b00000010)
			ptr->flags &= ~0b00000010;
		else
			ptr->flags |= 0b00000010;
		ptr = ptr->next;
	}
}

void		ft_all(t_env *e, char *inputs)
{
	t_str	*ptr;
	char	done;

	done = 0;
	if (!((inputs[0] == 'a' && inputs[1] == 0) &&
		(inputs[2] == 0)))
		return ;
	ptr = e->lst;
	while (ptr)
	{
		if (!(ptr->flags & 0b00000010))
		{
			ptr->flags |= 0b00000010;
			done = 1;
		}
		ptr = ptr->next;
	}
	if (done)
		return ;
	ptr = e->lst;
	while (ptr)
	{
		ptr->flags &= ~0b00000010;
		ptr = ptr->next;
	}
}

void		ft_home(t_env *e, char *inputs)
{
	if (!(inputs[0] == 27 && inputs[1] == 91 && inputs[2] == 72 &&
		inputs[3] == 0 && inputs[4] == 0 && inputs[5] == 0))
		return ;
	e->ptr->flags &= ~0b00000001;
	e->ptr = e->lst;
	e->ptr->flags |= 0b00000001;
}

void		ft_end(t_env *e, char *inputs)
{
	if (!(inputs[0] == 27 && inputs[1] == 91 && inputs[2] == 70 &&
		inputs[3] == 0 && inputs[4] == 0 && inputs[5] == 0))
		return ;
	e->ptr->flags &= ~0b00000001;
	while (e->ptr->next)
		e->ptr = e->ptr->next;
	e->ptr->flags |= 0b00000001;
}
