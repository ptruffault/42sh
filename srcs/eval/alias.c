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
#include "ft_printf.h"

static t_word	*ft_next_alias(t_word *w, t_word *w_alias, int boucl)
{
	t_word		*tmp;
	char		*save;

	save = w->word;
	if (++boucl < 10
		&& !(w_alias = ft_check_alias(w_alias, ft_get_set_shell(NULL), boucl)))
		return (w);
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
	return (w);
}

static t_word	*ft_alias_to_tword(t_word *w, char *val, int boucl)
{
	t_word	*w_alias;
	t_eval	e_alias;

	w_alias = NULL;
	if (++boucl < 10)
	{
		lexer(&e_alias, val);
		if (e_alias.s && e_alias.eval)
			w_alias = ft_get_words(&e_alias);
		ft_strdel(&e_alias.eval);
		ft_strdel(&e_alias.s);
		if (w_alias == NULL)
			return (w);
		return (ft_next_alias(w, w_alias, boucl));
	}
	return (w);
}

t_word			*ft_check_alias(t_word *head, t_shell *sh, int boucl)
{
	t_word	*w;
	char	*val;
	int		i;

	i = 1;
	w = head;
	while (w && ++boucl < 10)
	{
		i = (w->type == OPERATEUR ? 0 : i);
		if (i == 1 && w && 1 <= w->type && w->type <= 3
			&& (get_tenvv(sh->alias, w->word)))
		{
			val = get_tenvv_val(sh->alias, w->word);
			w = ft_alias_to_tword(w, val, boucl);
			if (val[ft_strlen(val) - 1] == ' ' && w->next)
				i = 0;
		}
		if (w && (w = w->next))
			i++;
	}
	return (head);
}
