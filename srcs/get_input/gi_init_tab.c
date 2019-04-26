/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gi_init_tab.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adi-rosa <adi-rosa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/16 14:36:42 by adi-rosa          #+#    #+#             */
/*   Updated: 2019/04/24 16:18:21 by fstadelw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell42.h"
#include "get_input.h"

void	ft_init_inputs_kval(t_edit *e, int x)
{
	e->kval[x++] = KEY_ENTER;
	e->kval[x++] = KEY_ARROW_UP;
	e->kval[x++] = KEY_ARROW_DOWN;
	e->kval[x++] = KEY_ARROW_LEFT;
	e->kval[x++] = KEY_ARROW_RIGHT;
	e->kval[x++] = KEY_OPTION_ARROW_UP;
	e->kval[x++] = KEY_OPTION_ARROW_DOWN;
	e->kval[x++] = KEY_OPTION_ARROW_LEFT;
	e->kval[x++] = KEY_OPTION_ARROW_RIGHT;
	e->kval[x++] = KEY_CTRL_C;
	e->kval[x++] = KEY_CTRL_D;
	e->kval[x++] = KEY_HOME;
	e->kval[x++] = KEY_END;
	e->kval[x++] = KEY_OPTION_C;
	e->kval[x++] = KEY_BACKSPACE;
	e->kval[x++] = KEY_DELETE;
	e->kval[x++] = KEY_OPTION_V;
	e->kval[x++] = KEY_SHIFT_ARROW_UP;
	e->kval[x++] = KEY_SHIFT_ARROW_DOWN;
	e->kval[x++] = KEY_SHIFT_ARROW_LEFT;
	e->kval[x++] = KEY_SHIFT_ARROW_RIGHT;
	e->kval[x++] = KEY_SHIFT_HOME;
	e->kval[x++] = KEY_SHIFT_END;
	e->kval[x++] = KEY_CTRL_R;
	e->kval[x++] = KEY_CTRL_L;
}

void	ft_init_inputs_tab(t_edit *e, int x)
{
	e->ft_tab[x++] = entry_key;
	e->ft_tab[x++] = hist_move_up;
	e->ft_tab[x++] = hist_move_do;
	e->ft_tab[x++] = curr_move_left;
	e->ft_tab[x++] = curr_move_right;
	e->ft_tab[x++] = ft_jump_line_up;
	e->ft_tab[x++] = ft_jump_line_down;
	e->ft_tab[x++] = ft_jp_word_left;
	e->ft_tab[x++] = ft_jp_word_right;
	e->ft_tab[x++] = reset_get_input;
	e->ft_tab[x++] = just_exit;
	e->ft_tab[x++] = ft_home_key;
	e->ft_tab[x++] = curr_go_last;
	e->ft_tab[x++] = ft_copy;
	e->ft_tab[x++] = delete_left;
	e->ft_tab[x++] = delete_on;
	e->ft_tab[x++] = ft_paste;
	e->ft_tab[x++] = ft_select_line_up;
	e->ft_tab[x++] = ft_select_line_down;
	e->ft_tab[x++] = ft_select_left;
	e->ft_tab[x++] = ft_select_right;
	e->ft_tab[x++] = ft_select_home;
	e->ft_tab[x++] = ft_select_end;
	e->ft_tab[x++] = ft_incr_search;
	e->ft_tab[x++] = gi_clear;
}

void	ft_init_print_modes(t_edit *e, int x)
{
	ft_init_inputs_kval(e, 0);
	ft_init_inputs_tab(e, 0);
	e->print_modes[x++] = ft_print_fast;
	e->print_modes[x++] = ft_print_edited;
	e->print_modes[x++] = ft_incremental_search;
}
