/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achazal <achazal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/18 02:14:06 by achazal           #+#    #+#             */
/*   Updated: 2015/02/25 05:33:18 by achazal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_select.h"
#include <stdlib.h>
#include <unistd.h>

void					ft_bzero(void *s, size_t n)
{
	char				*ptr;

	if (!n)
		return ;
	ptr = s;
	while (n--)
		*ptr++ = 0;
}

char					*ft_strjoin(char *s1, char *s2)
{
	register char		*str;
	register char		*ptr;

	if (s1 && !s2)
		return (ft_strdup(s1));
	else if (!s1 && s2)
		return (ft_strdup(s2));
	else if (!s1)
		return (NULL);
	if (!(str = (char *)malloc(sizeof(char) *
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

char					*ft_strjoinf1(char **s1, char *s2)
{
	char				*tmp;

	tmp = ft_strjoin(*s1, s2);
	free(*s1);
	s1 = NULL;
	return (tmp);
}

char					*ft_strjoinf2(char *s1, char **s2)
{
	char				*tmp;

	tmp = ft_strjoin(s1, *s2);
	free(*s2);
	s2 = NULL;
	return (tmp);
}

void					ft_putlststr(t_str *head)
{
	t_str				*ptr;

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
