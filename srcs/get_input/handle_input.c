/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_input.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptruffau <ptruffau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/13 13:14:33 by ptruffau          #+#    #+#             */
/*   Updated: 2019/04/24 16:18:26 by fstadelw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell42.h"
#include "get_input.h"

static int	handle_paste(unsigned long buf, t_edit *e)
{
	int					i;
	static union u_str	w_str;

	i = -1;
	w_str.buff = 0;
	ft_memset(w_str.str, 0, 9);
	w_str.buff = buf;
	while (w_str.str[++i] != 0)
	{
		if (w_str.str[i] != 9)
			if (!(ft_add_char(w_str.str[i], e)))
				return (FAILURE);
	}
	return (SUCCESS);
}

void		ft_incr_search(t_edit *e)
{
	e->mode = 2;
}

int			handle_input(unsigned long buf, t_edit *e)
{
	int				x;

	x = -1;
	while (++x < NUMBER_OF_KEYS)
	{
		if (e->kval[x] == buf)
		{
			if (x < 13)
			{
				e->select = -1;
				e->select_pos = 0;
			}
			e->ft_tab[x](e);
			if (x == 9 || x == 10)
				return (x);
			break ;
		}
	}
	if (x == NUMBER_OF_KEYS && buf == 9 && e->hist)
		return (tab_handle(e));
	if (x == NUMBER_OF_KEYS && e->hist)
		if (!(handle_paste(buf, e)))
			return (9);
	return (x);
}
