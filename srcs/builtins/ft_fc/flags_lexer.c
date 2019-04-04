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

int			flags_gestion(char *flags, char **av, int x)
{
	int		b;
	char	c;

	x = -1;
	while (++x < 6)
		flags[x] = '\0';
	x = 1;
	while (av[x] && av[x][0] == '-' && (av[x][1] < '0' || av[x][1] > '9'))
	{
		b = 1;
		while (av[x][b])
			if (av[x][b] == 'e' || av[x][b] == 'l'
					|| av[x][b] == 'n' || av[x][b] == 'r'
					|| av[x][b] == 's')
				check_doublons(flags, av[x][b++]);
			else
				return (error_c("fc: illegal option --", av[x][b]) + 1);
		++x;
	}
	flags_priority(flags);
	return (x);
}
