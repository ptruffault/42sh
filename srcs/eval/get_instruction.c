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
			if ((value = get_tenvv_val(sh->env, "HOME")))
			{
				tmp = ft_strplexp(w->word, tmp + 1, 0, value);
				ft_strdel(&w->word);
				w->word = tmp;
			}
	if (w && IS_EXP(w->type) && w->word)
		w->word = ft_exp_var(w->word, sh);
	return (w);
}

static t_word	*get_argv(t_tree *t, t_word *w)
{
	while (w && w->word && ft_isequal_env(w->word))
	{
		if (!check_name(w->word))
			break ;
					ft_printf("%s\n", w->word);
		w = maybe_expand(w);
			ft_printf("%s\n", w->word);
		if (w->paste && w->next)
		{

			w->next = maybe_expand(w->next);
			w->word[ft_strlen(w->word) - 1] = '\0';
			t->assign = ft_new_envv(t->assign, w->word, w->next->word, TMP);
			w = w->next;
		}
		else
			t->assign = ft_new_envv_equ(t->assign, w->word, TMP);
		w = w->next;
	}
	while (w && w->word && (IS_CMD(w->type) || w->type == NUL))
	{
		t->cmd = ft_addtword(t->cmd, w);
		w = w->next;
	}
	return (w);
}

static t_tree	*built_tree(t_tree *head, t_word *w, t_shell *sh)
{
	t_word	*tmp;
	t_tree	*tree;

	tmp = w;
	if (!head)
		return (NULL);
	tree = head;
	while (tmp && tmp->word)
	{
		if (tmp && (IS_CMD(tmp->type) || tmp->type == NUL))
			tmp = get_argv(tree, tmp);
		if (tmp && ((tmp->type == REDIRECT
			&& !(tmp = get_redirections(tree, tmp)))
			|| (tmp->type == OPERATEUR && !(tree = add_newttree(tree, tmp)))))
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
			|| (w->type == OPERATEUR && ft_strlen(w->word) > 2)
			|| (w->type == OPERATEUR && *w->word == ';'
				&& ft_strlen(w->word) > 1) || (w && w->type == REDIRECT
				&& ft_strchr(w->word, '<') && ft_strchr(w->word, '>')))
		{
			sh->env = ft_new_envv_int(sh->env, "?", 2, IN);
			return (error("syntax error near", w->word));
		}
		if (IS_CMD(w->type))
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
	if (!ft_check_grammar(w, sh) ||
	!(head = built_tree(new_tree(), w, sh)))
	{
		w = ft_free_tword(w);
		return (NULL);
	}
	ft_get_set_tree(head);
	w = ft_free_tword(w);
	return (head);
}
