/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptruffau <ptruffau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/04 14:10:52 by ptruffau          #+#    #+#             */
/*   Updated: 2019/04/24 16:58:58 by fstadelw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "shell42.h"

static void	ft_write_special(char s, char c, int *i)
{
	*i += 1;
	if (c == 't')
		write(1, "\t", 1);
	else if (c == 'n')
		write(1, "\n", 1);
	else if (c == 'f')
		write(1, "\f", 1);
	else if (c == 'r')
		write(1, "\r", 1);
	else if (c == 'v')
		write(1, "\v", 1);
	else if (c == 'a')
		write(1, "\a", 1);
	else if (c == '\\')
		write(1, "\\", 1);
	else if (c == '\"')
		write(1, "\"", 1);
	else
	{
		*i -= 1;
		write(1, &s, 1);
	}
}

static void	ft_putstr_echo(char *s)
{
	int i;

	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == '\\')
		{
			if (s[i + 1] == '\\')
				i++;
			if (s[i + 1] != '\0')
				ft_write_special(s[i], s[i + 1], &i);
			else
				write(1, "\\", 1);
			i++;
		}
		else if (s[i] != '`')
		{
			write(1, &s[i], 1);
			i++;
		}
		else
			i++;
	}
}

static int	only_n(char *str)
{
	int		i;

	i = -1;
	while (str[++i])
		if (str[i] != 'n')
			return (0);
	return (1);
}

int			ft_echo(char **input, t_process *p)
{
	int i;
	int opts_n;

	opts_n = 0;
	i = 0;
	if (p->fd[1] == -1)
	{
		error("echo: write error: Bad file descriptor", NULL);
		return (1);
	}
	while (input[i] && input[i][0] == '-' && only_n(&input[i][1]))
		i++;
	opts_n = (i > 0) ? 1 : 0;
	while (*input && input[i])
	{
		ft_putstr_echo(input[i++]);
		if (input[i] != 0)
			ft_putchar(' ');
	}
	if (opts_n == 0)
		ft_putchar('\n');
	return (0);
}
