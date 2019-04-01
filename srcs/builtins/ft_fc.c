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
	while (av[x] && av[x][0] == '-' && (av[x][1] < '0' || av[x][1] > '9'))
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
    ft_printf("%d\n", x);
	return (x);
}

void list_hist(t_fc *fc)
{
    int reverse;

    reverse = 0;
    if (ft_strchr(fc->flags, 'r'))
        reverse = 1;
    if (search_in_hist_parser(fc) == FAILURE)
        return ;
}

void fc_init_first_last(t_fc *fc, int pos)
{
    fc->first = 0;
    fc->last = 0;
    fc->first_ = NULL;
    fc->last_ = NULL;
    
    if (fc->av[pos])
        {
            if (fc->av[pos][0] >= '0' && fc->av[pos][0] <= '9')
                fc->first = ft_atoi(fc->av[pos]) == 0 ? -1 : ft_atoi(fc->av[pos]);
            else
                fc->first_ = fc->av[pos];
            if (fc->av[pos + 1])
            {
                if (fc->av[pos + 1][0] >= '0' && fc->av[pos + 1][0] <= '9')
                fc->last = ft_atoi(fc->av[pos + 1]) == 0 ? -1 : ft_atoi(fc->av[pos + 1]);
              else
                 fc->last_ = fc->av[pos + 1];
            }
        }
    else
    {
        fc->first = -15;
        fc->last = 0;
    }
}

int ft_fc(t_shell *shell, char **argv)
{
    t_fc *fc;
    int x;
    char c;
    int i;

    if (!(fc = malloc(sizeof(t_fc) * 1)))
        return (1);
    x = -1;
    fc->av = argv;
    fc->shell = shell;
    fc->hist = shell->hist;
    fc->hist_first = NULL;
    fc->hist_last = NULL;
    if ((i = flags_gestion(fc->flags, fc->av, 0)) == FAILURE)
        return (-1);
    ft_printf("%d\n", i);
    while (fc->flags[++x])
        if (fc->flags[x] == 'l' || fc->flags[x] == 'e' || fc->flags[x] == 's')
            {
                c = fc->flags[x];
                fc->flags[x] = fc->flags[0];
                fc->flags[0] = c;
                break;
            }
    if (fc->flags[0] == 'l')
        list_hist(fc);
    if (fc->flags[0] == 'e')
        ;
    if (fc->flags[0] == 's')
        ;
    free(fc);
    return (0);
}
