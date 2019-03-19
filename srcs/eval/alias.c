/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alias.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptruffau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/07 16:41:00 by ptruffau          #+#    #+#             */
/*   Updated: 2019/03/19 11:43:05 by stdenis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <shell42.h>

static t_word	*ft_alias_to_tword(t_word *w, char *val)
{
	t_word	*w_alias;
	t_eval	e_alias;
	t_word	*tmp;

	e_alias = lexer(val);
	w_alias = ft_get_words(&e_alias);
	ft_strdel(&e_alias.eval);
	ft_strdel(&e_alias.s);
	ft_strdel(&w->word);
	w->word = ft_strdup(w_alias->word);
	if (w_alias->next)
	{
		tmp = w_alias->next;
		while (tmp && tmp->next)
			tmp = tmp->next;
		tmp->next = w->next;
		w->next = w_alias->next;
	}
	w_alias->next = NULL;
	ft_free_tword(w_alias);
	return (w);
}

t_word			*ft_check_alias(t_word *head, t_shell *sh)
{
	t_word	*tmp_w;
	t_word 	*save;
	char	*val;
	int		i;

	tmp_w = head;
	i = 1;
	while (tmp_w)
	{
		if (tmp_w->type == OPERATEUR)
			i = 0;
		if (i == 1 && tmp_w && IS_CMD(tmp_w->type) && tmp_w->type != QUOTE
		&& (val = get_tenvv_val(sh->alias, tmp_w->word)))
		{
			save = tmp_w->next;
			tmp_w = ft_alias_to_tword(tmp_w, val);
			tmp_w = save;
		}
		else
			tmp_w = tmp_w->next;
		i++;
	}
	return (head);
}
