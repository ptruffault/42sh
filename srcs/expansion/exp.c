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
		ft_printf("{%s}\n", w->word);
		w =w->next;
	}
}

t_word 		*ft_word_paste(t_word *head)
{
	t_word *w;
	t_word *tmp;

	w = head;
	tmp = NULL;
	while (w)
	{
		tmp = w;
		while (w && w->paste && w->next && w->next->word)
		{
			if ((tmp->word = ft_strappend(&tmp->word, w->next->word)))
			{
				tmp->paste = w->next->paste;
				tmp = ft_deltword(w, w->next);
			}
		}
		w = (w ? w->next : w);
	}
	return (head);
}

t_word		*ft_expention(t_word *w)
{
	t_shell	*sh;
	t_word	*head;

	head = w;
	if (!(sh = ft_get_set_shell(NULL)))
		return (head);
	while (w)
	{
		if (w && IS_EXP(w->type) && w->word)
			w->word = ft_exp_var(w->word, sh);
		w = (w ? w->next : w);
	}
	if (head && ((!(head = ft_word_paste(head)))
		|| !(head = ft_exp_home_var(head, sh->env))))
		return (NULL);
	//ft_putword(head);
	return (head);
}
