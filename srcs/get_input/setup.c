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

static void	ft_init_inputs_kval(t_edit *e)
{
	e->kval[0] = KEY_ENTER;
	e->kval[1] = KEY_ARROW_UP;
	e->kval[2] = KEY_ARROW_DOWN;
	e->kval[3] = KEY_ARROW_LEFT;
	e->kval[4] = KEY_ARROW_RIGHT;
	e->kval[5] = KEY_OPTION_ARROW_UP;
	e->kval[6] = KEY_OPTION_ARROW_DOWN;
	e->kval[7] = KEY_OPTION_ARROW_LEFT;
	e->kval[8] = KEY_OPTION_ARROW_RIGHT;
	e->kval[9] = KEY_CTRL_C;
	e->kval[10] = KEY_CTRL_D;
	e->kval[11] = KEY_HOME;
	e->kval[12] = KEY_END;

	e->kval[13] = KEY_OPTION_C;

	e->kval[14] = KEY_BACKSPACE;
	e->kval[15] = KEY_DELETE;
	e->kval[16] = KEY_OPTION_V;

	e->kval[17] = KEY_SHIFT_ARROW_UP;
	e->kval[18] = KEY_SHIFT_ARROW_DOWN;
	e->kval[19] = KEY_SHIFT_ARROW_LEFT;
	e->kval[20] = KEY_SHIFT_ARROW_RIGHT;
	e->kval[21] = KEY_SHIFT_HOME;
	e->kval[22] = KEY_SHIFT_END;
}

static void	ft_init_inputs_tab(t_edit *e)
{
	ft_init_inputs_kval(e);
	e->ft_tab[0] = entry_key;
	e->ft_tab[1] = hist_move_up;
	e->ft_tab[2] = hist_move_do;
	e->ft_tab[3] = curr_move_left;
	e->ft_tab[4] = curr_move_right;
	e->ft_tab[5] = ft_jump_line_up;
	e->ft_tab[6] = ft_jump_line_down;
	e->ft_tab[7] = ft_jp_word_left;
	e->ft_tab[8] = ft_jp_word_right;
	e->ft_tab[9] = reset_get_input;
	e->ft_tab[10] = just_exit;
	e->ft_tab[11] = ft_home_key;
	e->ft_tab[12] = curr_go_last;

	e->ft_tab[13] = ft_copy;

	e->ft_tab[14] = delete_left;
	e->ft_tab[15] = delete_on;
	e->ft_tab[16] = ft_paste;

	e->ft_tab[17] = ft_select_line_up;
	e->ft_tab[18] = ft_select_line_down;
	e->ft_tab[19] = ft_select_left;
	e->ft_tab[20] = ft_select_right;
	e->ft_tab[21] = ft_select_home;
	e->ft_tab[22] = ft_select_end;
}

t_edit	init_tedit(t_shell *sh)
{
	t_hist *tmp;

	ft_update_windows(&sh->e);
	ft_init_inputs_tab(&sh->e);
	sh->e.edited = FALSE;
	sh->e.curr = 0;
	sh->e.pos = 0;
	sh->e.select = -1;
	if ((tmp = new_hist()))
	{
		tmp->next = sh->hist;
		sh->e.hist = tmp;
		if (tmp->next)
			tmp->next->prev = tmp;
		tmp->s = ft_strnew(2);
	}
	return (sh->e);
}
