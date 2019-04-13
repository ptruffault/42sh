/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arrow_move.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adi-rosa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/29 11:52:40 by adi-rosa          #+#    #+#             */
/*   Updated: 2019/03/26 17:21:55 by stdenis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <get_input.h>

void	curr_move_right(t_edit *e)
{
	if (e->max_char < e->pos)
	{
		if (((e->curr + 1) - (size_t)e->pos_z) == e->width)
		{
			if (e->pos_y > 0)
			{
				e->pos_z += (e->pos_y > (int)e->width) ? (int)e->width : e->pos_y;
				e->pos_y -= (e->pos_y > (int)e->width) ? (int)e->width : e->pos_y;
			}
		}
	}
	if ((size_t)e->curr < ft_strlen(e->hist->s))
		e->curr++;
}

void	curr_move_left(t_edit *e)
{
	if (e->max_char < e->pos)
	{
		if (e->curr == (size_t)e->pos_z)
		{
			if (e->pos_z > 0)
			{
				e->pos_y += (e->pos_z > (int)e->width) ? (int)e->width : e->pos_z;
				e->pos_z -= (e->pos_z > (int)e->width) ? (int)e->width : e->pos_z;
			}
		}
	}
	if (e->curr > 0)
		e->curr--;
}

void	curr_go_last(t_edit *e)
{
	e->curr = ft_strlen(e->hist->s);
	e->pos_y = 0;
	if (e->curr > e->max_char)
		e->pos_z = (int)e->curr - (int)e->max_char;
	else
		e->pos_z = 0;
}

void	ft_home_key(t_edit *e)
{
	e->curr = 0;
	e->pos_z = 0;
	if (ft_strlen(e->hist->s) > e->max_char)
		e->pos_y = (int)(ft_strlen(e->hist->s) - e->max_char);
	else
		e->pos_y = 0;
}
