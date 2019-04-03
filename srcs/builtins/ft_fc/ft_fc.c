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
	return (x);
}

void	fc_init_first_last(t_fc *fc, int pos)
{
	if (fc->av[pos])
	{
		if ((fc->av[pos][0] >= '0' && fc->av[pos][0] <= '9') || fc->av[pos][0] == '-')
			fc->first = ft_atoi(fc->av[pos]) == 0 ? -1 : ft_atoi(fc->av[pos]);
		else
			fc->first_ = fc->av[pos];
		if (fc->av[pos + 1])
		{
			if ((fc->av[pos + 1][0] >= '0' && fc->av[pos + 1][0] <= '9') || fc->av[pos + 1][0] == '-')
				fc->last = ft_atoi(fc->av[pos + 1]) == 0 ? -1 : ft_atoi(fc->av[pos + 1]);
			else
				fc->last_ = fc->av[pos + 1];
		}
		else
			fc->last = -1;
	}
	ft_printf("\nFIRST->%d | LAST->%d\n", fc->first, fc->last);
}

int		ft_fc(t_shell *shell, char **argv)
{
	t_fc	*fc;
	int		x;
	char	c;
	int		i;

	if (!shell->hist && !shell->hist->next)
		return (1);
	if (!(fc = malloc(sizeof(t_fc) * 1)))
		return (1);
	x = -1;
	fc->av = argv;
	fc->shell = shell;
	fc->hist = shell->hist->next;
	fc->hist_first = NULL;
	fc->hist_last = NULL;
	fc->first = -16;
	fc->last = -1;
	fc->first_ = NULL;
	fc->last_ = NULL;
	if ((i = flags_gestion(fc->flags, fc->av, 0)) == FAILURE)
		return (-1);
	while (fc->flags[++x])
		if (fc->flags[x] == 'l' || fc->flags[x] == 'e' || fc->flags[x] == 's')
		{
			c = fc->flags[x];
			fc->flags[x] = fc->flags[0];
			fc->flags[0] = c;
			break ;
		}
	if (fc->flags[0] != 's')
		fc_init_first_last(fc, i);
	if (fc->flags[0] == 'l')
		ft_fc_option_l(fc);
	else if (fc->flags[0] == 'e')
		;
	else if (fc->flags[0] == 's')
		ft_fc_option_s(fc, i);
	free(fc);
	return (0);
}
