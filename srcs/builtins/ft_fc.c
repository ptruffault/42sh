/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fc.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adi-rosa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/29 14:47:53 by adi-rosa          #+#    #+#             */
/*   Updated: 2019/03/29 14:47:54 by adi-rosa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell42.h"

void	check_doublons(char *flags, char c)
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

int		flags_gestion(char *flags, char **av, int x)
{
	int b;

	x = -1;
	while (++x < 6)
		flags[x] = '\0';
	x = 1;
	while (av[x] && av[x][0] == '-')
	{
		b = 1;
		while (av[x][b])
		{
			if (av[x][b] == 'e' || av[x][b] == 'l'
					|| av[x][b] == 'n' || av[x][b] == 'r'
					|| av[x][b] == 's')
				check_doublons(flags, av[x][b++]);
			else
			{
                ft_printf("fc: illegal option -- %c\n", av[x][b]);
				return (FAILURE);
			}
		}
		++x;
	}
	return (x);
}

int ft_fc(t_shell *shell, char **argv)
{
    char flags[6];
    (void)shell;
    (void)argv;
    if (flags_gestion(flags, argv, 0) == FAILURE)
        return (-1);
    return (0);
}
