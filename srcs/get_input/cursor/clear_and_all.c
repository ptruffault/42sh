/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_and_all.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adi-rosa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/29 11:57:43 by adi-rosa          #+#    #+#             */
/*   Updated: 2019/03/26 17:21:55 by stdenis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <get_input.h>

void	reset_tedit(t_edit *e)
{
	e->curr = 0;
	e->pos = 0;
	e->select = -1;
	e->select_pos = 0;
	e->hist->s = ft_strnew(3);
}

void	reset_get_input(t_edit *e)
{
	ft_strdel(&e->tmp);
	if (!e->hist)
		return ;
	while (e->hist->prev)
		e->hist = e->hist->prev;
	ft_strdel(&e->hist->s);
	if (e->hist->next)
		e->hist->next->prev = NULL;
	free(e->hist);
}

void	just_exit(t_edit *e)
{
	t_shell *sh;

	sh = ft_get_set_shell(NULL);
	if (!e->hist || !e->hist->s || !*e->hist->s)
	{
		if (sh->heredoc == 1)
		{
			sh->heredoc = 0;
			sh->e.edited = TRUE;
		}
		if (e->hist)
			reset_get_input(e);
		e->hist = NULL;
	}
}
