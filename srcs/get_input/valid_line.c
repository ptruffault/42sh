/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adi-rosa <adi-rosa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/29 11:57:43 by adi-rosa          #+#    #+#             */
/*   Updated: 2019/04/24 16:20:55 by fstadelw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/ioctl.h>
#include "shell42.h"
#include "get_input.h"

static void	setup_key(char *error[7], t_edit *e)
{
	error[0] = "\ncmdand";
	error[1] = "\ncmdor";
	error[2] = "\npipe";
	error[3] = "\nquote";
	error[4] = "\ndquote";
	error[5] = "\nbackslash";
	error[6] = "\nparenth";
	if (e->tmp == NULL)
		e->tmp = e->hist->s;
	else
		e->tmp = ft_strjoin_fr(e->tmp, e->hist->s);
	e->hist->s = e->tmp;
}

int			check_eval(char *str)
{
	char	*tmp;

	tmp = str;
	while ((tmp = ft_strchr(tmp, 'o')))
	{
		if (ft_strchr(tmp + 1, 'o') - tmp + 1 == 3)
			return (0);
		if (ft_strstr(tmp + 1, "oo") - tmp + 1 == 4)
			return (0);
		tmp++;
	}
	tmp = str;
	while ((tmp = ft_strstr(tmp, "oo")))
	{
		if (ft_strstr(tmp + 1, "oo") - tmp + 1 == 4)
			return (0);
		if (ft_strchr(tmp + 1, 'o') - tmp + 1 == 3)
			return (0);
		tmp++;
	}
	return (1);
}

void			set_head_al(t_shell *sh)
{
	int		i;

	i = -1;
	while (++i < 150)
		sh->head_al[i] = NULL;
}

int				check_grammar_alias(t_word *w)
{
	t_word	*head;

	head = w;
	while (w)
	{
		if (head->type == OPERATEUR
			|| (w->type == OPERATEUR && w->next && w->next->type == OPERATEUR)
			|| (w->type == OPERATEUR && !w->next && !ft_strequ("&", w->word)
				&& !ft_strequ(";", w->word)))
			return (1);
		w = w->next;
	}
	return (0);
}

void		check_error_alias(t_edit *e, t_word *head)
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

void		check_alias(t_edit *e)
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

void		check_hist_and_alias(t_edit *e)
{
	if (ft_get_set_shell(NULL)->heredoc == 0
		&& check_for_hist_exp(e) == SUCCESS)
		e->edited = FALSE;
	if (e->edited == TRUE)
		check_alias(e);
}

void		entry_key(t_edit *e)
{
	t_eval	eval;
	char	*error[7];

	if (e->mode == 2 && ft_incr_add(e) == SUCCESS)
		return ;
	setup_key(error, e);
	lexer(&eval, e->hist->s);
	if (eval.eval != NULL && check_eval(eval.eval)
		&& ft_get_set_shell(NULL)->heredoc == 0 && eval.err > 1)
	{
		reset_tedit(e);
		eval.err = (eval.err >= 2) ? eval.err - 2 : eval.err;
		e->tmp = ft_strjoin_add_edit(&e->tmp, "\n", eval.err);
		ft_others_prompt(ft_get_set_shell(NULL), error[eval.err]);
	}
	else
	{
		e->tmp = NULL;
		e->edited = TRUE;
		check_hist_and_alias(e);
	}
	ft_strdel(&eval.eval);
	ft_strdel(&eval.s);
}
