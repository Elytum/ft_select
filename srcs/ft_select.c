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
#include <fcntl.h>

static int		ft_pushback(t_str **head, char *str)
{
	t_str		*tmp;
	t_str		*ptr;
	char		*p;

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

static void		ft_loop(t_env *e)
{
	char		inputs[6];

	write(e->tty, tgetstr("vi", NULL), 6);
	ft_putselect(e);
	ft_bzero(inputs, 6);
	e->put = 0;
	while ((read(0, inputs, 6)) != EOF)
	{
		ft_delete(e, inputs);
		ft_up_down(e, inputs);
		ft_left_right(e, inputs);
		ft_select(e, inputs);
		ft_enter(e, inputs);
		ft_echap(e, inputs);
		ft_reset(e, inputs);
		ft_reverse(e, inputs);
		ft_all(e, inputs);
		ft_home(e, inputs);
		ft_end(e, inputs);
		ft_putselect(e);
		ft_bzero(inputs, 6);
	}
}

static void		init_term(void)
{
	int			sucess;
	char		*termbuf;
	char		*term;

	termbuf = (char *)malloc(sizeof(char*) * TERM_BUF);
	term = getenv("TERM");
	if (term == NULL)
	{
		write(2, "Specify a terminal with 'setenv TERM'\n", 38);
		exit(0);
	}
	if ((sucess = tgetent(termbuf, term)) <= 0)
	{
		if (sucess < 0)
			write(2, "Can't access to termcaps database\n", 34);
		if (sucess == 0)
			write(2, "Terminal Type not defined\n", 26);
		exit(0);
	}
}

static t_env	*ft_init(int ac, char **av)
{
	t_env		*e;
	int			w;

	init_term();
	if (!ac || !av || !*av || !*(++av))
		return (NULL);
	if (!(e = (t_env *)malloc(sizeof(t_env))))
		return (NULL);
	e->lst = NULL;
	e->maxy = 0;
	e->maxx = 0;
	e->x = 0;
	e->y = 0;
	while (*av && ++e->maxy)
	{
		if (!(w = ft_pushback(&(e->lst), *av++)))
			return (NULL);
		if (w > e->maxx)
			e->maxx = w;
	}
	e->ptr = e->lst;
	e->p = ft_get_params();
	e->lst->flags |= 0b00000001;
	return (e);
}

int				main(int ac, char **av)
{
	t_env		*e;

	if (!(e = ft_init(ac, av)))
		return (-1);
	ft_init_signals(e);
	ft_loop(e);
	return (0);
}
