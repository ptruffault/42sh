/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_instrction.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptruffau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/07 14:20:35 by ptruffau          #+#    #+#             */
/*   Updated: 2019/03/26 17:21:55 by stdenis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell42.h"

static t_word	*maybe_expand(t_word *w)
{
	t_shell	*sh;
	char	*tmp;
	char	*value;

	sh = ft_get_set_shell(NULL);
	if (w && (tmp = ft_strchr(w->word, '=')) && tmp[1] == '~')
		if (tmp[2] == '\0' || tmp[2] == '/')
			if ((value = retrieve_home(NULL, sh->env)))
			{
				tmp = ft_strplexp(w->word, tmp + 1, 0, value);
				ft_strdel(&w->word);
				w->word = tmp;
			}
	if (w && 1 <= w->type && w->type <= 3 && w->word)
		w->word = ft_exp_var(w->word, sh, FALSE);
	return (w);
}

static t_word	*get_argv(t_tree **t, t_word *w)
{
	while (w && w->word && ft_isequal_env(w->word))
	{
		if (!check_name(w->word))
			break ;
		w = maybe_expand(w);
		if (w && w->paste && w->next)
		{
			w->next = maybe_expand(w->next);
			w->word[ft_strlen(w->word) - 1] = '\0';
			t[0]->ass = ft_new_envv(t[0]->ass, w->word, w->next->word, TMP);
			w = w->next;
		}
		else
			t[0]->ass = ft_new_envv_equ(t[0]->ass, w->word, TMP);
		if (w)
			w = w->next;
	}
	while (w && w->word && ((1 <= w->type && w->type <= 4) || w->type == NUL))
	{
		t[0]->cmd = ft_addtword(t[0]->cmd, w);
		w = w->next;
	}
	return (w);
}

static t_tree	*built_tree(t_word *w, t_shell *sh)
{
	t_word	*tmp;
	t_tree	*tree;
	t_tree	*head;

	tmp = w;
	if (!(head = new_tree()))
		return (NULL);
	tree = head;
	while (tmp && tmp->word)
	{
		if (tmp && ((1 <= tmp->type && tmp->type <= 4) || tmp->type == NUL))
			tmp = get_argv(&tree, tmp);
		if (tmp && ((tmp->type == REDIRECT
					&& !(tmp = get_redirections(tree, tmp)))
				|| (tmp->type == OPERATEUR && !(tree = newttree(tree, tmp)))))
		{
			error("syntax error", NULL);
			sh->env = ft_new_envv_int(sh->env, "?", 2, IN);
			return (ft_free_tree(head));
		}
		if (tmp)
			tmp = tmp->next;
	}
	return (head);
}

int				ft_check_grammar(t_word *w, t_shell *sh)
{
	int		cmd;
	t_word	*head;

	cmd = 0;
	head = w;
	while (w)
	{
		if (head->type == OPERATEUR
			|| (w->type == OPERATEUR && w->next && w->next->type == OPERATEUR)
			|| (w->type == OPERATEUR && !w->next)
			|| (w->type == OPERATEUR && ft_strlen(w->word) > 2)
			|| (w->type == OPERATEUR && *w->word == ';'
				&& ft_strlen(w->word) > 1) || (w && w->type == REDIRECT
				&& ft_strchr(w->word, '<') && ft_strchr(w->word, '>')))
		{
			sh->env = ft_new_envv_int(sh->env, "?", 2, IN);
			return (error("syntax error near", w->word));
		}
		if (1 <= w->type && w->type <= 4)
			cmd++;
		w = w->next;
	}
	if (!cmd)
		sh->env = ft_new_envv_int(sh->env, "?", 1, IN);
	return (!cmd ? warning("nothing to do", NULL) : 1);
}

t_tree			*get_tree(char *input, t_shell *sh)
{
	t_tree	*head;
	t_word	*w;

	if (!input || ft_isempty(input) || !ft_check_ascii(input)
		|| !(w = eval_line(input)))
		return (NULL);
	if (!ft_check_grammar(w, sh)
		|| !(head = built_tree(w, sh)))
	{
		w = ft_free_tword(w);
		return (NULL);
	}
	ft_get_set_tree(head);
	w = ft_free_tword(w);
	return (head);
}
