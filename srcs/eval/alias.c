/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alias.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptruffau <ptruffau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/07 16:41:00 by ptruffau          #+#    #+#             */
/*   Updated: 2019/04/24 16:57:38 by fstadelw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "shell42.h"

static t_word	*reorder_w(t_word *w, t_word **w_a, t_word **tmp, t_word **jic)
{
	int		count;
	t_word	*save;

	count = 1;
	save = w->next;
	*tmp = (*w_a)->next;
	while ((*tmp)->next && (*tmp)->next->word && ++count)
		*tmp = (*tmp)->next;
	if ((*tmp)->next != NULL)
		*jic = (*tmp)->next;
	(*tmp)->next = w->next;
	w->next = (*w_a)->next;
	w = save;
	return ((*tmp));
}

static t_word	*should_paste_alias(t_word *w, t_word *w_alias)
{
	t_word	*jic;
	char	*tmp;

	jic = NULL;
	tmp = w->word;
	if (w_alias->next && w_alias->paste)
	{
		if (!(w->word = ft_strappend(&w->word, w_alias->next->word)))
			w->word = tmp;
		jic = w_alias->next;
		w_alias->next = w_alias->next->next;
		jic->next = NULL;
		jic = ft_free_tword(jic);
	}
	return (w_alias);
}

static t_word	*ft_next_alias(t_word *w, t_word *w_alias)
{
	t_word		*tmp;
	t_word		*jic;
	char		*save;

	save = w->word;
	jic = NULL;
	if (!(w->word = ft_strdup(w_alias->word)))
		w->word = save;
	else
	{
		w->type = w_alias->type;
		ft_strdel(&save);
	}
	w_alias = should_paste_alias(w, w_alias);
	if (w_alias->next && w_alias->next->word)
		w = reorder_w(w, &w_alias, &tmp, &jic);
	else if (w_alias->next)
		jic = w_alias->next;
	w_alias->next = NULL;
	ft_free_tword(w_alias);
	ft_free_tword(jic);
	return (w);
}

static t_word	*ft_alias_to_tword(t_word *w, char *val, t_shell *sh, int *doit)
{
	t_word			*w_alias;
	t_eval			e_alias;

	*doit += 1;
	if (ft_isempty(val))
		return (ft_alias_empty(w));
	w_alias = NULL;
	lexer(&e_alias, val);
	if (e_alias.s && e_alias.eval)
		w_alias = ft_get_words(&e_alias);
	ft_strdel(&e_alias.eval);
	ft_strdel(&e_alias.s);
	if (w_alias && (ft_check_in_head(sh->head_al, w_alias->word, sh->loop)))
	{
		w_alias = ft_check_alias(w_alias, sh, ++sh->loop);
		ft_strdel(&sh->head_al[sh->loop--]);
	}
	if (w_alias == NULL)
		return (w);
	return (ft_next_alias(w, w_alias));
}

t_word			*ft_check_alias(t_word *head, t_shell *sh, int k)
{
	t_word	*w;
	char	*val;
	int		doit;
	int		i;

	i = 0;
	doit = 0;
	w = head;
	while (w && ++i && sh->loop < 150)
	{
		i = check_order_alias(w, &doit, i);
		if (w->word && i == 1 && 1 <= w->type && w->type <= 3
			&& (val = get_tenvv_val(sh->alias, w->word)))
		{
			if (ft_strlen(val) > 0 && val[ft_strlen(val) - 1] == ' ')
				i = 0;
			if (sh->head_al[k] != NULL)
				ft_strdel(&sh->head_al[k]);
			if ((sh->head_al[k] = ft_strdup(w->word)))
				w = ft_alias_to_tword(w, val, sh, &doit);
		}
		w = w ? w->next : w;
	}
	ft_strdel(&sh->head_al[k]);
	return (head);
}
