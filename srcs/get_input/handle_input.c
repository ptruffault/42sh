/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_input.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptruffau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/13 13:14:33 by ptruffau          #+#    #+#             */
/*   Updated: 2019/03/19 19:04:57 by stdenis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <get_input.h>

int		handle_input(unsigned long buf, t_edit *e)
{
	int				x;

	x = -1;
	while (++x < NUMBER_OF_KEYS)
	{
		if (e->kval[x] == buf)
		{
			if (x < 13)
				e->select = -1;
			e->ft_tab[x](e);
			if (x == 9)
				return (9);
			break ;
		}
	}
	if (x == NUMBER_OF_KEYS && ft_isascii(buf) && e->hist)
		ft_add_char((char)buf, e);
	return (x);
}
