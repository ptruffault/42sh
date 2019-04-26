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
#include "ft_printf.h"

static char		*ft_get_varname(char *s)
{
	char	*ptr;
	size_t	i;

	i = 0;
	ptr = s + 1;
	if (*ptr == '!' || *ptr == '?' || *ptr == '$')
		return (ft_strndup(ptr, 1));
	while (ptr[i] && ((ft_strchr("@_{}", e->s[e->curr]) 
			|| ft_isalpha(e->s[e->curr]) || ft_isdigit(e->s[e->curr]))))
		i++;
	return (ft_strsub(s, (unsigned int)(ptr - s), i));
}

static char		*ft_exp_envv_var(char *ret, t_shell *sh, int *i)
{
	char	*name;
	char	*value;
	char	*tmp;

	name = NULL;
	value = NULL;
	if (!(name = ft_get_varname(&ret[*i])))
		ft_strdel(&ret);
	else if (!(value = get_tenvv_val(sh->env, name)))
		value = "";
	if (name && (tmp = ft_strplexp(ret, &ret[*i], (int)ft_strlen(name), value)))
	{
		ft_strdel(&ret);
		ret = tmp;
		*i = *i + (*value ? (int)ft_strlen(value) - 1 : -1);
	}
	ft_strdel(&name);
	return (ret);
}

static t_word	*ft_exp_home_var(t_word *head, t_envv *envv)
{
	char	*tmp;
	char	*val;
	t_word	*w;

	tmp = NULL;
	w = head;
	while (w)
	{
		if (w->word && *w->word == '~' && checktilde(w)
			&& 0 < w->type && w->type <= 2
			&& (val = retrieve_home(NULL, envv))
			&& (tmp = ft_strpull(w->word, w->word, 0, val)))
		{
			ft_strdel(&w->word);
			w->word = tmp;
		}
		w = w->next;
	}
	return (head);
}

char			*ft_exp_var(char *ret, t_shell *sh, t_bool quoting)
{
	int i;
	int j;

	i = -1;
	while (ret && *ret && ret[++i])
	{
		if (quoting && (ret[i] == '\\' || ret[i] == '\''))
			break ;
		if (!quoting && ret[i] == '\\')
		{
			j = i++;
			while (ret[j++])
				ret[j - 1] = ret[j];
		}
		if (ret[i] == '$' && ret[i + 1])
		{
			if (ret[i + 1] == '{')
			{
				if (!(ret = ft_exp_param(ret, &ret[i], sh)))
					return (NULL);
				i = -1;
			}
			else if (!(ret = ft_exp_envv_var(ret, sh, &i)))
				return (NULL);
		}
	}
	if (quoting)
		ret = ft_clear_quote(ret);
	return (ret);
}

t_tree			*ft_expention(t_tree *t)
{
	t_shell	*sh;
	t_word	*w;
	t_tree	*tmp;

	tmp = t;
	sh = ft_get_set_shell(NULL);
	while (tmp)
	{
		w = t->cmd;
		while (w)
		{
			if (w && 1 <= w->type && w->type <= 3 && w->word)
				w->word = ft_exp_var(w->word, sh, FALSE);
			w = w->next;
		}
		tmp = ft_word_paste(tmp);
		tmp->cmd = ft_exp_home_var(tmp->cmd, sh->env);
		tmp = (tmp->o_type == O_PIPE ? tmp->next : NULL);
	}
	return (t);
}
