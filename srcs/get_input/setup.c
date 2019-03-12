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
	e->kval[0] = TOUCHE_CTRL_C;
	e->kval[1] = ARROW_LEFT;
	e->kval[2] = ARROW_RIGHT;
	e->kval[3] = TOUCHE_HOME;
	e->kval[4] = TOUCHE_END;
	e->kval[5] = TOUCHE_OPT_RIGHT;
	e->kval[6] = TOUCHE_OPT_LEFT;
	e->kval[7] = TOUCHE_OPT_C;
	e->kval[8] = TOUCHE_OPT_V;
	e->kval[9] = TOUCHE_CTRL_D;
	e->kval[10] = ARROW_UP;
	e->kval[11] = ARROW_DOWN;
	e->kval[12] = TOUCHE_SUPPR;
	e->kval[13] = TOUCHE_DEL;
	e->kval[14] = TOUCHE_CTRL_L;
	e->kval[15] = TOUCHE_SELECT_LEFT;
	e->kval[16] = TOUCHE_SELECT_RIGHT;
	e->kval[17] = TOUCHE_MAJ_END;
	e->kval[18] = TOUCHE_MAJ_HOME;
	e->kval[19] = TOUCHE_MAJ_ARROW_UP;
	e->kval[20] = TOUCHE_MAJ_ARROW_DOWN;
	e->kval[21] = KEY_ENTER;
}

static void	ft_init_inputs_tab(t_edit *e)
{
	ft_init_inputs_kval(e);
	e->ft_tab[0] = reset_get_input;
	e->ft_tab[1] = curr_move_left;
	e->ft_tab[2] = curr_move_right;
	e->ft_tab[3] = ft_home_key;
	e->ft_tab[4] = curr_go_last;
	e->ft_tab[5] = ft_jp_word_right;
	e->ft_tab[6] = ft_jp_word_left;
	e->ft_tab[7] = ft_copy;
	e->ft_tab[8] = ft_paste;
	e->ft_tab[9] = just_exit;
	e->ft_tab[10] = hist_move_up;
	e->ft_tab[11] = hist_move_do;
	e->ft_tab[12] = delete_left;
	e->ft_tab[13] = delete_on;
	e->ft_tab[14] = clear_term;
	e->ft_tab[15] = ft_select_left;
	e->ft_tab[16] = ft_select_right;
	e->ft_tab[17] = ft_select_end;
	e->ft_tab[18] = ft_select_home;
	e->ft_tab[19] = ft_jump_line_up;
	e->ft_tab[20] = ft_jump_line_down;
	e->ft_tab[21] = entry_key;
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
		tmp->s = ft_strnew(2);
	}
	return (sh->e);
}
