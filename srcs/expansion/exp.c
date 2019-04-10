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

char	*ft_exp_home_var(char *ret, t_envv *envv)
{
	char	*tmp;
	char	*val;

	tmp = NULL;
	if ((val = get_tenvv_val(envv, "HOME"))
	&& (tmp = ft_strpull(ret, ret, 0, val)))
	{
		ft_strdel(&ret);
		return (tmp);
	}
	ft_strdel(&ret);
	return (NULL);
}

char		*ft_exp_var(char *ret, t_shell *sh)
{
	int i;

	i = -1;
	while (ret && *ret && ret[++i])
	{
		if (ret[i] == '$' && ret[i + 1] && (i == 0 || ret[i - 1] != '\\'))
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

t_word		*ft_expention(t_word *w)
{
	t_shell	*sh;
	t_word	*head;

	head = w;
	if (!(sh = ft_get_set_shell(NULL)))
		return (head);
	while (w)
	{
		if (1 <= w->type && w->type <= 2 && *w->word ==  '~')
			w->word = ft_exp_home_var(w->word, sh->env);
		if (IS_EXP(w->type) && w->word)
			w->word = ft_exp_var(w->word, sh);
		w = w->next;
	}
	return (head);
}
