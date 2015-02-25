/* ************************************************************************** */
/*			                                                               */
/*                                                        :::      ::::::::   */
/*   ft_select.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achazal <achazal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/18 02:14:06 by achazal           #+#    #+#             */
/*   Updated: 2015/02/18 02:14:08 by achazal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>

int			ft_putc(int c)
{
	return (write(1, &c, 1));
}

void		*ft_memalloc(size_t size)
{
	void	*memory;
	char	*explorer;

	if (!size || !(memory = (void *)malloc(size)))
		return (NULL);
	explorer = (char *)memory;
	if (memory != NULL)
		while (size--)
	*explorer++ = 0;
	return (memory);
}

int			ft_strlen(char *str)
{
	char	*ptr;

	ptr = str;
	while (*ptr)
		ptr++;
	return (ptr - str);
}

void		ft_putstr(char *str)
{
	char	*ptr;

	ptr = str;
	while (*ptr)
		ptr++;
	write(1, str, ptr - str);
}

char		*ft_strdup(char *str)
{
	char	*nstr;
	char	*ptr;

	ptr = str;
	while (*ptr)
		ptr++;
	if (!(nstr = (char *)malloc(sizeof(char) * (ptr - str + 1))))
		return (NULL);
	ptr = nstr;
	while (*str)
		*ptr++ = *str++;
	*ptr = '\0';
	return (nstr);
}