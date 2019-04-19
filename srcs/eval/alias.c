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

static t_word	*ft_next_alias(t_word *w, t_word *w_alias, int boucl)
{
	t_word		*tmp;
	char		*save;

	save = w->word;
	if (boucl++ < 10)
		w_alias = ft_check_alias(w_alias, ft_get_set_shell(NULL), boucl);
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
	lexer(&e_alias, val);
	if (e_alias.s && e_alias.eval)
		w_alias = ft_get_words(&e_alias);
	ft_strdel(&e_alias.eval);
	ft_strdel(&e_alias.s);
	if (w_alias == NULL)
		return (w);
	return (ft_next_alias(w, w_alias, boucl));
}


//to add (protect '!')
t_word 			*ft_simple_check(t_word *head)
{
	t_word *w;
	t_word *prev;
	int i;

	i = 1;
	prev = NULL;
	w = head;
	while (w)
	{
		i = w->type == OPERATEUR ? 0 : i;
		if (i == 1 && w && ft_strequ(w->word, "!")
			&& 1 <= w->type && w->type <= 2)
		{
			w = ft_deltword(prev, w);
			head = !prev ? w : head;
		}
		w = w->next;
		prev = w;
		i++;
	}
	return (head);
}

t_word			*ft_check_alias(t_word *head, t_shell *sh, int boucl)
{
	t_word	*w;
	char	*val;
	int i;

	i = 1;
	w = head;
	while (w)
	{
		i = (w->type == OPERATEUR ? 0 : i);
		if (i == 1 && w && 1 <= w->type && w->type <= 3 
			&& (val = get_tenvv_val(sh->alias, w->word)))
		{
			w = ft_alias_to_tword(w, val, boucl);
			if (val[ft_strlen(val) - 1] == ' ' && w->next)
				i = 0;
		}
		if (w && w->word)
			i++;
		w = w->next;
	}
	return (ft_simple_check(head));
}
