/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fc_option_l.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adi-rosa <adi-rosa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/01 16:07:34 by adi-rosa          #+#    #+#             */
/*   Updated: 2019/04/24 17:03:10 by fstadelw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "ft_printf.h"
#include "shell42.h"

static void	print_line(t_fc *fc, int nb)
{
	char	**split;
	int		i;

	i = -1;
	split = ft_strsplit(fc->hist_first->s, '\n');
	while (split[++i])
	{
		if (nb == 0)
		{
			if (i == 0)
				ft_printf("%d\t%s\n", fc->hist_first->nb, split[i]);
			else
				ft_printf("\t%s\n", split[i]);
		}
		else
			ft_printf("\t%s\n", split[i]);
	}
	ft_freestrarr(&split);
}

static void	print_hist_opt_l(t_fc *fc, short way)
{
	int	nb;

	nb = ft_strchr(fc->flags, 'n') ? 1 : 0;
	if (way == 0)
		while (fc->hist_first && fc->hist_first->nb >= fc->hist_last->nb)
		{
			print_line(fc, nb);
			fc->hist_first = fc->hist_first->next;
		}
	else if (way == 1)
		while (fc->hist_first && fc->hist_first->nb <= fc->hist_last->nb)
		{
			print_line(fc, nb);
			fc->hist_first = fc->hist_first->prev;
		}
}

int			ft_fc_option_l(t_fc *fc)
{
	short	way;
	t_hist	*tmp;

	if (search_in_hist_parser(fc, 3) == FAILURE)
		return (1);
	if (ft_strchr(fc->flags, 'r'))
	{
		tmp = fc->hist_first;
		fc->hist_first = fc->hist_last;
		fc->hist_last = tmp;
	}
	way = fc->hist_first->nb < fc->hist_last->nb ? 1 : 0;
	print_hist_opt_l(fc, way);
	return (0);
}
