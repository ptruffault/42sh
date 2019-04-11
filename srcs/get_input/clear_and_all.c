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

void	setup_key(char *error[7], t_edit *e)
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
		e->tmp = ft_strjoin_add_if(&e->tmp, &e->hist->s, "\n");
	e->hist->s = e->tmp;
}

int		check_eval(char *str)
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

void	entry_key(t_edit *e)
{
	t_eval	eval;
	t_shell	*sh;
	char	*error[7];

	if (e->mode == 2 && ft_incr_add(e) == SUCCESS)
		return ;
	sh = ft_get_set_shell(NULL);
	setup_key(error, e);
	lexer(&eval, e->hist->s);
	if (eval.eval != NULL && check_eval(eval.eval)
		&& sh->heredoc == 0 && eval.err > 1)
	{
		e->curr = 0;
		e->pos = 0;
		e->select = -1;
		e->select_pos = 0;
		e->hist->s = ft_strnew(3);
		eval.err = (eval.err >= 2) ? eval.err - 2 : eval.err;
		ft_others_prompt(ft_get_set_shell(NULL), error[eval.err]);
	}
	else
	{
		e->tmp = NULL;
		e->edited = TRUE;
	}
	if (check_for_hist_exp(e) == SUCCESS)
	{
		e->tmp = NULL;
		e->edited = FALSE;
	}
	ft_strdel(&eval.eval);
	ft_strdel(&eval.s);
}

void	clear_term(t_edit *e)
{
	term_actions(HOME_POS);
	term_actions(CLEAR);
	e->pos = 0;
}

void	reset_get_input(t_edit *e)
{
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
		while (e->hist->prev)
			e->hist = e->hist->prev;
		if (e->hist->next)
			e->hist->next->prev = NULL;
		ft_strdel(&e->hist->s);
		free(e->hist);
		e->hist = NULL;
	}
}
