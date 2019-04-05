/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fc_option_l.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adi-rosa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/01 16:07:34 by adi-rosa          #+#    #+#             */
/*   Updated: 2019/04/01 16:07:35 by adi-rosa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell42.h"

static void	print_hist_opt_l(t_fc *fc, short way)
{
	int	nb;

	nb = ft_strchr(fc->flags, 'n') ? 1 : 0;
	if (way == 0)
	{
		while (fc->hist_first->nb >= fc->hist_last->nb)
		{
			if (nb == 0)
				ft_printf("%-10d%s\n", fc->hist_first->nb, fc->hist_first->s);
			else
				ft_printf("%s\n", fc->hist_first->s);
			fc->hist_first = fc->hist_first->next;
		}
	}
	else if (way == 1)
	{
		while (fc->hist_first->nb <= fc->hist_last->nb)
		{
			if (nb == 0)
				ft_printf("%-10d%s\n", fc->hist_first->nb, fc->hist_first->s);
			else
				ft_printf("%s\n", fc->hist_first->s);
			fc->hist_first = fc->hist_first->prev;
		}
	}
}

void		ft_fc_option_l(t_fc *fc)
{
	short	way;
	t_hist	*tmp;

	if (search_in_hist_parser(fc, 3) == FAILURE)
		return ;
	tmp = fc->hist_first;
	fc->hist_first = fc->hist_last;
	fc->hist_last = tmp;
	if (ft_strchr(fc->flags, 'r'))
	{
		tmp = fc->hist_first;
		fc->hist_first = fc->hist_last;
		fc->hist_last = tmp;
	}
	ft_printf("FIRST->[%s][%d] | LAST->[%s][%d]\n", fc->hist_first->s, fc->hist_first->nb, fc->hist_last->s, fc->hist_last->nb);
	way = fc->hist_first->nb < fc->hist_last->nb ? 1 : 0;
	print_hist_opt_l(fc, way);
}
