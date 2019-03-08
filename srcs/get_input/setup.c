/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptruffau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/13 13:23:52 by ptruffau          #+#    #+#             */
/*   Updated: 2019/02/05 12:29:43 by adi-rosa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/get_input.h"

t_edit	init_tedit(t_shell *sh)
{
	t_hist *tmp;

	ft_update_windows(&sh->e);
	sh->e.edited = FALSE;
	sh->e.curr = 0;
	sh->e.pos = 0;
	sh->e.select = -1;
	if ((tmp = new_hist()))
	{
		tmp->next = sh->hist;
		sh->e.hist = tmp;
		tmp->s = ft_strnew(2);
	}
	return (sh->e);
}
