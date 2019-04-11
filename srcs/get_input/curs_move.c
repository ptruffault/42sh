/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   curs_move.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptruffau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/13 13:08:59 by ptruffau          #+#    #+#             */
/*   Updated: 2019/03/26 17:21:55 by stdenis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <get_input.h>

size_t	how_much_cr(t_edit *e)
{
	size_t	i;
	int		count;

	i = 0;
	count = 0;
	while (e->hist && e->hist->s && e->hist->s[i])
	{
		if (e->hist->s[i] == '\n')
			count++;
		i++;
	}
	return (count);
}

void	curs_reset(t_edit *e)
{
	size_t	y;
	size_t	total;
	int		count;

	count = how_much_cr(e);
	while (count-- > 0)
		term_actions(CURSOR_UP);
	if (e->pos_z == 0 && e->pos_y == 0)
		y = e->pos;
	else
	{
		total = (e->pos - e->pos_z - e->pos_y);
		y = (total >= e->width) ? total : e->width;
	}
	if (e->width != 0)
	{
		while (y > e->width)
		{
			y = y - e->width;
			term_actions(CURSOR_UP);
		}
	}
	term_goto(CURSOR_MHORIZ, 0, 0);
	e->pos = 0;
}
