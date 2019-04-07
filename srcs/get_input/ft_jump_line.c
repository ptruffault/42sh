/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_jump_line.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adi-rosa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/18 12:40:09 by adi-rosa          #+#    #+#             */
/*   Updated: 2019/03/26 17:21:55 by stdenis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <get_input.h>

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
			curr_move_left(e);
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
