/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expention.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptruffau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/08 16:10:38 by ptruffau          #+#    #+#             */
/*   Updated: 2019/03/26 17:21:55 by stdenis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell42.h"

static char	*ft_get_varname(char *s)
{
	char	*ptr;
	int		i;

	i = 0;
	ptr = s + 1;
	if (*ptr == '!' || *ptr == '?' || *ptr == '$')
		return (ft_strndup(ptr, 1));
	while (ptr[i] && (ptr[i] == '_' || ft_isalpha(ptr[i])
	|| ft_isdigit(ptr[i]) || ptr[i] == '~' || ptr[i] == '@'))
		i++;
	return (ft_strsub(s, ptr - s, i));
}

static char	*ft_exp_envv_var(char *ret, char *ptr, t_shell *sh)
{
	char	*name;
	char	*value;
	char	*tmp;

	name = NULL;
	value = NULL;
	if (!(name = ft_get_varname(ptr))
	|| !(value = get_tenvv_val(sh->env, name)))
		ft_strdel(&ret);
	else if (name && (tmp = ft_strpull(ret, ptr, ft_strlen(name), value)))
	{
		ft_strdel(&ret);
		ret = tmp;
	}
	ft_strdel(&name);
	return (ret);
}

t_word	*ft_exp_home_var(t_word *head, t_envv *envv)
{
	char	*tmp;
	char	*val;
	t_word *w;

	tmp = NULL;
	w = head;
	while (w)
	{
		if (w->word && *w->word == '~' && 0 < w->type && w->type <= 2
		&& (val = get_tenvv_val(envv, "HOME"))
		&& (tmp = ft_strpull(w->word, w->word, 0, val)))
		{
			ft_strdel(&w->word);
			w->word = tmp;
		}
		w = w->next;
	}
	return (head);
}

char		*ft_exp_var(char *ret, t_shell *sh)
{
	int i;

	i = -1;
	while (ret && *ret && ret[++i])
	{
		if (ret[i] == '$' && ret[i + 1])
		{
			if (ret[i + 1] == '{')
			{
				if (!(ret = ft_exp_param(ret, &ret[i], sh)))
					return (NULL);
				i = -1;
			} 
			else if (ret[i + 1] != '{' && !(ret = ft_exp_envv_var(ret, &ret[i], sh)))
				return (NULL);
		}
	}
	return (ret);
}

void ft_putword(t_word *w)
{
	while (w)
	{
		if (w->word)
			ft_printf("{%s}\n", w->word);
		w = w->next;
	}
}

t_tree *ft_word_paste(t_tree *t)
{
	t_word *head;
	t_word *new;
	t_word *tmp;

	tmp = t->cmd;
	head = NULL;
	while (tmp)
	{
		if (tmp->type == NUL && tmp->paste == TRUE)
		{
			tmp = tmp->next;
		}
		else if (tmp->paste && tmp->next && tmp->next->word)
		{
			if ((new = new_tword()))
			{
				new->word = ft_strdup(tmp->word);
				while (tmp && tmp->paste && tmp->next && tmp->next->word)
				{
					new->word = ft_strappend(&new->word, tmp->next->word);
					tmp = tmp->next;
				}
				tmp = tmp->next;
				head = ft_addtword(head, new);
				ft_free_tword(new);
			}
		}
		else
		{
			head = ft_addtword(head, tmp);
			tmp = tmp->next;
		}
	}
	t->cmd = ft_free_tword(t->cmd);
	t->cmd = head;
	return (t);
}

t_tree *ft_expention(t_tree *t)
{
	t_shell	*sh;
	t_word	*w;

	w = t->cmd;
	sh = ft_get_set_shell(NULL);
	while (w)
	{
		if (w && IS_EXP(w->type) && w->word)
			w->word = ft_exp_var(w->word, sh);
		w = (w ? w->next : w);
	}
	t = ft_word_paste(t);
	t->cmd = ft_exp_home_var(t->cmd, sh->env);
	//ft_putword(t->cmd);
	return (t);
}
