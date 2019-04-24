/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_jump_line.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adi-rosa <adi-rosa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/18 12:40:09 by adi-rosa          #+#    #+#             */
/*   Updated: 2019/04/24 16:17:26 by fstadelw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell42.h"
#include "get_input.h"

void	ft_jump_line_up(t_edit *e)
{
	size_t	width;

	width = e->width;
	if (e->curr >= e->width)
		while (width-- > 0)
			curr_move_left(e);
}

void	ft_select_line_up(t_edit *e)
{
	if (e->select == -1)
	{
		e->select = 1;
		e->select_pos = e->curr;
	}
	ft_jump_line_up(e);
}

void	ft_jump_line_down(t_edit *e)
{
	size_t	width;

	width = e->width;
	if (ft_strlen(e->hist->s) - e->curr >= e->width)
		while (width-- > 0)
			curr_move_right(e);
}

void	ft_select_line_down(t_edit *e)
{
	if (e->select == -1)
	{
		e->select = 1;
		e->select_pos = e->curr;
	}
	ft_jump_line_down(e);
}
