/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   curs_move.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptruffau <ptruffau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/13 13:08:59 by ptruffau          #+#    #+#             */
/*   Updated: 2019/04/24 16:14:37 by fstadelw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell42.h"
#include "get_input.h"

static size_t	how_much_cr(t_edit *e)
{
	size_t	i;
	size_t	count;

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

void			curs_reset(t_edit *e)
{
	size_t	y;
	size_t	total;
	size_t	count;

	count = how_much_cr(e);
	while (count-- > 0)
		term_actions(CURSOR_UP);
	if (e->pos_z == 0 && e->pos_y == 0)
		y = e->pos;
	else
	{
		if ((size_t)e->pos_z + (size_t)e->pos_y > e->pos)
			total = 0;
		else
			total = (e->pos - (size_t)e->pos_z - (size_t)e->pos_y);
		y = (total >= e->width) ? total : e->width;
	}
	while (e->width != 0 && y > e->width)
	{
		y = y - e->width;
		term_actions(CURSOR_UP);
	}
	term_goto(CURSOR_MHORIZ, 0, 0);
	e->pos = 0;
}
