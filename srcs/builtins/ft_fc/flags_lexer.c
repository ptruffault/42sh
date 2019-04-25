/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flags_lexer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adi-rosa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/04 13:30:37 by adi-rosa          #+#    #+#             */
/*   Updated: 2019/04/04 13:30:39 by adi-rosa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell42.h"

static void	check_doublons(char *flags, char c)
{
	int x;

	x = 0;
	while (flags[x])
	{
		if (flags[x] == c)
			return ;
		++x;
	}
	flags[x] = c;
	return ;
}

static void	flags_priority(char *flags)
{
	char	c;
	int		x;

	x = 0;
	while (flags[++x])
		if (flags[x] == 'l' || flags[x] == 'e' || flags[x] == 's')
		{
			c = flags[x];
			flags[x] = flags[0];
			flags[0] = c;
			break ;
		}
}

static int	error_options_fc(int ret, const char opts)
{
	error_c("fc: invalid option :", opts);
	ft_putstr_fd("usage: -fc [-e editor] [-lnr] [first] [last] or", 2);
	ft_putendl_fd("fc -s [old=new] [command]", 2);
	return (ret);
}

int			flags_gestion(char *flags, char **av, int x)
{
	int		b;
	bool	opts;

	x = -1;
	while (++x < 6)
		flags[x] = '\0';
	x = 1;
	opts = true;
	while (opts && av[x] && av[x][0] == '-'
			&& (av[x][1] < '0' || av[x][1] > '9'))
	{
		b = 1;
		while (opts && av[x][b])
			if (av[x][b] == 'e' || av[x][b] == 'l' || av[x][b] == 'n'
				|| av[x][b] == 'r' || av[x][b] == 's')
				check_doublons(flags, av[x][b++]);
			else if (av[x][b] != '-')
				return (error_options_fc(1, av[x][b]));
			else if (av[x][b] == '-')
				opts = false;
			else
				b++;
		++x;
	}
	flags_priority(flags);
	return (x);
}
