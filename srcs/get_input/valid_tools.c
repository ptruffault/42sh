/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stdenis <stdenis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/18 15:33:46 by stdenis           #+#    #+#             */
/*   Updated: 2019/04/24 17:08:11 by stdenis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell42.h"
#include "get_input.h"

static int		check_grammar_alias(t_word *w)
{
	while (w->next)
		w = w->next;
	if (w->type == OPERATEUR && !ft_strequ("&", w->word)
		&& !ft_strequ(";", w->word))
		return (1);
	return (0);
}

static void		check_error_alias(t_edit *e, t_word *head)
{
	if (check_grammar_alias(head))
	{
		reset_tedit(e);
		e->tmp = ft_strjoin_add_edit(&e->tmp, "\n", 2);
		ft_others_prompt(ft_get_set_shell(NULL), "\nop");
	}
	else
	{
		e->tmp = NULL;
		e->edited = TRUE;
	}
}

void			set_head_al(t_shell *sh)
{
	int		i;

	i = -1;
	while (++i < 150)
		sh->head_al[i] = NULL;
}

void			check_alias(t_edit *e)
{
	t_word	*head;
	t_eval	ev;
	t_shell	*sh;
	char	*error[7];

	head = NULL;
	setup_key(error, e);
	sh = ft_get_set_shell(NULL);
	e->edited = FALSE;
	lexer(&ev, e->hist->s);
	sh->loop = 0;
	set_head_al(sh);
	if (ev.s && ev.eval && (head = ft_get_words(&ev)))
	{
		ft_strdel(&ev.eval);
		ft_strdel(&ev.s);
		head = ft_check_alias(head, sh, 0);
		check_error_alias(e, head);
	}
	else
		e->edited = TRUE;
	ft_free_tword(head);
}
