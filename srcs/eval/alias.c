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

	count = 1;
	*tmp = (*w_a)->next;
	while ((*tmp)->next && (*tmp)->next->word && count++)
		*tmp = (*tmp)->next;
	if ((*tmp)->next != NULL)
		*jic = (*tmp)->next;
	(*tmp)->next = w->next;
	w->next = (*w_a)->next;
	while (--count >= 0 && w->next)
		w = w->next;
	return (w);
}

t_word			*ft_next_alias(t_word *w, t_word *w_alias)
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
	if (w_alias->next && w_alias->next->word)
		w = reorder_w(w, &w_alias, &tmp, &jic);
	else if (w_alias->next)
		jic = w_alias->next;
	w_alias->next = NULL;
	ft_free_tword(w_alias);
	ft_free_tword(jic);
	return (w);
}

static t_word	*ft_alias_to_tword(t_word *w, char *val, t_shell *sh, int loop)
{
	t_word			*w_alias;
	t_eval			e_alias;
	static char		*ptr;

	w_alias = NULL;
	lexer(&e_alias, val);
	if (e_alias.s && e_alias.eval)
		w_alias = ft_get_words(&e_alias);
	ft_strdel(&e_alias.eval);
	ft_strdel(&e_alias.s);
	if (w_alias && (!ft_strequ(ptr, val))
		&& (!ft_strequ(w->word, w_alias->word)))
	{
		ptr = w->word;
		w_alias = ft_check_alias(w_alias, sh, loop);
	}
	ptr = NULL;
	if (w_alias == NULL)
		return (w);
	return (ft_next_alias(w, w_alias));
}

t_word			*ft_check_alias(t_word *head, t_shell *sh, int loop)
{
	t_word	*w;
	char	*val;
	int		i;

	i = 0;
	w = head;
	while (w && ++i && loop < 100)
	{
		i = (w->type == OPERATEUR ? 0 : i);
		if (w->word && i == 1 && 1 <= w->type && w->type <= 3
			&& (get_tenvv(sh->alias, w->word)) && ++loop < 100)
		{
			val = get_tenvv_val(sh->alias, w->word);
			if (ft_strlen(val) > 0 && val[ft_strlen(val) - 1] == ' '
				&& w->next && w->next->word)
				i = 0;
			w = ft_alias_to_tword(w, val, sh, loop);
		}
		w = w ? w->next : w;
	}
	return (head);
}
