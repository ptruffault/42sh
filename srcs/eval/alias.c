/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alias.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptruffau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/07 16:41:00 by ptruffau          #+#    #+#             */
/*   Updated: 2019/03/26 17:21:55 by stdenis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell42.h"

static t_word	*ft_next_alias(t_word *w, t_word *w_alias)
{
	t_word		*tmp;
	char		*save;
	static int	inf;

	save = w->word;
	if (!(w->word = ft_strdup(w_alias->word)))
		w->word = save;
	else
		ft_strdel(&save);
	if (w_alias->next)
	{
		tmp = w_alias->next;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = w->next;
		w->next = w_alias->next;
	}
	w_alias->next = NULL;
	ft_free_tword(w_alias);
	if (inf++ < 100)
		return (ft_check_alias(w, ft_get_set_shell(NULL), 1, NULL));
	return (w);
}

static t_word	*ft_alias_to_tword(t_word *w, char *val)
{
	t_word	*w_alias;
	t_eval	e_alias;

	w_alias = NULL;
	lexer(&e_alias, val);
	if (e_alias.s && e_alias.eval)
		w_alias = ft_get_words(&e_alias);
	ft_strdel(&e_alias.eval);
	ft_strdel(&e_alias.s);
	if (w_alias == NULL)
		return (w);
	return (ft_next_alias(w, w_alias));
}

static t_word	*ft_fuck_that_norme(t_word *w, t_word **prev)
{
	w = w->next;
	*prev = w;
	return (w);
}

t_word			*ft_check_alias(t_word *head, t_shell *sh, int i, t_word *prev)
{
	t_word	*w;
	char	*val;

	w = head;
	while (w)
	{
		i = w->type == OPERATEUR ? 0 : i;
		if (i == 1 && w && ft_strequ(w->word, "!")
			&& 1 <= w->type && w->type <= 4 && w->type != QUOTE
			&& w->type != DQUOTE)
		{
			w = ft_deltword(prev, w);
			head = !prev ? w : head;
		}
		else if (i == 1 && w && 1 <= w->type && w->type <= 4 && w->type != QUOTE
			&& (val = get_tenvv_val(sh->alias, w->word)))
		{
			w = ft_alias_to_tword(w, val);
			w = head;
		}
		else if (w)
			w = ft_fuck_that_norme(w, &prev);
		i++;
	}
	return (head);
}
