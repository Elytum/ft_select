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

char                    *ft_strjoin(char *s1, char *s2)
{
    register char       *str;
    register char       *ptr;

    if (s1 && !s2)
        return (ft_strdup(s1));
    else if (!s1 && s2)
        return (ft_strdup(s2));
    else if (!s1)
        return (NULL);
    if (!(str = (char *)malloc(sizeof(char) * \
        (ft_strlen(s1) + ft_strlen(s2) + 1))))
        return (NULL);
    ptr = str;
    while (*s1)
        *ptr++ = *s1++;
    while (*s2)
        *ptr++ = *s2++;
    *ptr = '\0';
    return (str);
}

char		*ft_strjoinf1(char **s1, char *s2)
{
	char	*tmp;

	tmp = ft_strjoin(*s1, s2);
	free(*s1);
	s1 = NULL;
	return (tmp);
}

char		*ft_strjoinf2(char *s1, char **s2)
{
	char	*tmp;
	
	tmp = ft_strjoin(s1, *s2);
	free(*s2);
	s2 = NULL;
	return (tmp);
}

void		ft_putselect(t_env *e)
{
	t_str	*pos;
	char	*buffer;

	// buffer = ft_strdup(tgetstr("cl", (char **)(&e->p->buf)));
	buffer = ft_strdup(tgoto(tgetstr("cm", (char **)(&e->p->buf)), 0, 0));
	buffer = ft_strjoinf1(&buffer, tgetstr("cd", (char **)(&e->p->buf)));
	pos = e->lst;
	while (pos)
	{
		if (pos->flags & 0b00000001)
			buffer = ft_strjoinf1(&buffer, tgetstr("us", (char **)(&e->p->buf)));
		if (pos->flags & 0b00000010)
			buffer = ft_strjoinf1(&buffer, tgetstr("so", (char **)(&e->p->buf)));
		buffer = ft_strjoinf1(&buffer, pos->str);
		buffer = ft_strjoinf1(&buffer, "\n");
		if (pos->flags & 0b00000001)
			buffer = ft_strjoinf1(&buffer, tgetstr("ue", (char **)(&e->p->buf)));
		if (pos->flags & 0b00000010)
			buffer = ft_strjoinf1(&buffer, tgetstr("se", (char **)(&e->p->buf)));
		pos = pos->next;
	}
	buffer = ft_strjoinf1(&buffer, tgoto(tgetstr("cm", (char **)(&e->p->buf)), e->x, e->y));
	tputs(buffer, 1, ft_putc);
	free(buffer);
}

void		ft_delete(t_env *e, char *inputs)
{
	t_str	*tmp;

	if (!(inputs[0] == 127 && inputs[1] == 0 && inputs[2] == 0 &&
		inputs[3] == 0 && inputs[5] == 0 && inputs[5] == 0) &&
		!(inputs[0] == 27 && inputs[1] == 91 && inputs[2] == 51 &&
		inputs[3] == 126 && inputs[5] == 0 && inputs[5] == 0))
		return ;
	e->put = 1;
	if (!(e->ptr->next))
		exit (0);
	if (e->ptr->past)
	{
		e->ptr->past = e->ptr->next;
		(e->ptr->past)->next = e->ptr->next;
		(e->ptr->next)->past = e->ptr->past;
		tmp = e->ptr->past;
	}
	else
	{
		e->ptr->next->past = NULL;
		e->y++;
		tmp = e->ptr->next;
	}
	free(e->ptr);
	e->ptr = tmp;
	(void)tmp;
}

void		ft_arrows(t_env *e, char *inputs)
{
	// dprintf(1, "Inputs : %i %i %i %i %i %i\n", inputs[0], inputs[1], inputs[2], inputs[3], inputs[4], inputs[5]);
	// sleep(2);
	if (!((inputs[0] == 27 && inputs[1] == 91) && (inputs[2] == 65 ||
		inputs[2] == 66) && inputs[3] == 0 && inputs[4] == 0 &&
		inputs[5] == 0))
		return ;
	e->put = 1;
	e->ptr->flags &= ~0b00000001;
	if (inputs[2] == 65) // UP
	{
		if (e->ptr->past)
			e->ptr = e->ptr->past;
		else
		{
			e->ptr = e->lst;
			while (e->ptr->next)
				e->ptr = e->ptr->next;
		}
	} // DOWN
	else 
	{
		if (e->ptr->next)
			e->ptr = e->ptr->next;
		else
			e->ptr = e->lst;
	}
	e->ptr->flags |= 0b00000001;
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

void		ft_loop(t_env *e)
{
	char	inputs[6];

	ft_putselect(e);
	// tputs(tgoto(tgetstr("cm", (char **)(&e->p->buf)), e->x, e->y), 1, ft_putc);
	ft_bzero(inputs, 6);
	e->put = 0;
	while ((read(0, inputs, 6)) != EOF)
	{
		// dprintf(1, "Inputs : %i %i %i %i %i %i\n", inputs[0], inputs[1], inputs[2], inputs[3], inputs[4], inputs[5]);
		ft_delete(e, inputs);
		ft_arrows(e, inputs);
		ft_select(e, inputs);
		if (e->put == 1 && !(e->put = 0))
			ft_putselect(e);
		ft_bzero(inputs, 6);
		usleep(40000);
	}
	while (1)
		;
}

int 		main(int ac, char **av)
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
	e->lst->next->flags |= 0b00000010;
	e->lst->next->next->flags |= 0b00000001;
	ft_loop(e);
	return (0);
	(void)ac;
}
