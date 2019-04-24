/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adi-rosa <adi-rosa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/01 17:57:42 by adi-rosa          #+#    #+#             */
/*   Updated: 2019/04/24 16:18:37 by fstadelw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell42.h"
#include "get_input.h"

static void	bottom_start_hist(t_edit *e, char *input)
{
	t_hist *hist;

	hist = ft_get_set_shell(NULL)->hist;
	while (input && hist)
	{
		if (ft_str_startwith(hist->s, input) != 0)
		{
			ft_strdel(&e->hist->s);
			e->hist->s = ft_strdup(hist->s);
			return ;
		}
		hist = hist->next;
	}
}

void		hist_move_up(t_edit *e)
{
	if (!e->head || ft_get_set_shell(NULL)->heredoc == 1)
		return ;
	ft_delete_line(e);
	if (e->head == e->hist && e->hist->s[0] != '\0')
		bottom_start_hist(e, e->hist->s);
	else if (e->head)
	{
		if (e->head->next != NULL)
			e->head = e->head->next;
		ft_strdel(&e->hist->s);
		e->hist->s = ft_strdup(e->head->s);
		if (e->hist->s == NULL)
			e->hist->s = ft_strnew(3);
	}
	if (e->hist->s)
		e->curr = ft_strlen(e->hist->s);
	e->pos_y = 0;
	if (e->curr > e->max_char)
		e->pos_z = (int)(e->curr - e->width + 2);
	else
		e->pos_z = 0;
	e->select = -1;
	ft_print_fast(e);
}

void		hist_move_do(t_edit *e)
{
	if (!e->head || ft_get_set_shell(NULL)->heredoc == 1)
		return ;
	ft_delete_line(e);
	if (e->head->prev != NULL)
		e->head = e->head->prev;
	ft_strdel(&e->hist->s);
	if (e->head == e->hist || e->head->s == NULL)
		e->hist->s = ft_strnew(3);
	else
		e->hist->s = ft_strdup(e->head->s);
	if (e->hist->s)
		e->curr = ft_strlen(e->hist->s);
	e->pos_y = 0;
	if (e->curr > e->max_char)
		e->pos_z = (int)(e->curr - e->width + 2);
	else
		e->pos_z = 0;
	e->select = -1;
	ft_print_fast(e);
}
