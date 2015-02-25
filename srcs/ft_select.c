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
#include <unistd.h>

static int	ft_pushback(t_str **head, char *str)
{
	t_str	*tmp;
	t_str	*ptr;
	char	*p;

	if (!head || !str || !(tmp = (t_str *)malloc(sizeof(t_str))) ||
		!(tmp->str = ft_strdup(str)))
		return (0);
	tmp->flags = 0;
	tmp->next = NULL;
	tmp->past = NULL;
	if (!*head)
		*head = tmp;
	else
	{
		ptr = *head;
		while (ptr->next)
			ptr = ptr->next;
		ptr->next = tmp;
		tmp->past = ptr;
	}
	p = str;
	while (*p)
		p++;
	return (p - str);
}

void		ft_putlststr(t_str *head)
{
	t_str	*ptr;

	ptr = head;
	write(1, "{ ", 2);
	while (ptr)
	{
		ft_putstr(ptr->str);
		ptr = ptr->next;
		ft_putstr((ptr) ? ", " : " ");
	}
	write(1, "}\n", 2);
}

void		ft_loop(t_env *e)
{
	char	inputs[6];

	ft_putselect(e);
	ft_bzero(inputs, 6);
	e->put = 0;
	tputs(tgetstr("vi", (char **)(&e->p->buf)), 1, ft_putc);
	while ((read(0, inputs, 6)) != EOF)
	{
		ft_delete(e, inputs);
		ft_arrows(e, inputs);
		ft_select(e, inputs);
		ft_enter(e, inputs);
		if (e->put == 1 && !(e->put = 0))
			ft_putselect(e);
		ft_bzero(inputs, 6);
		usleep(40000);
	}
}

int			main(int ac, char **av)
{
	t_env	*e;
	int		w;

	if (!av || !*av || !*(++av))
		return (-1);
	if (!(e = (t_env *)malloc(sizeof(t_env))))
		return (-1);
	e->lst = NULL;
	e->height = 0;
	e->width = 0;
	e->x = 0;
	e->y = 0;
	while (*av && ++e->height)
	{
		if (!(w = ft_pushback(&(e->lst), *av++)))
			return (-1);
		if (w > e->width)
			e->width = w;
	}
	e->ptr = e->lst;
	e->p = ft_get_params();
	e->lst->flags |= 0b00000001;
	ft_loop(e);
	return (0);
	(void)ac;
}
