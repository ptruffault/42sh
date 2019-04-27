/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eval_tools.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptruffau <ptruffau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/07 14:19:48 by ptruffau          #+#    #+#             */
/*   Updated: 2019/04/24 16:54:29 by fstadelw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "shell42.h"

static size_t	ft_twordlen(t_word *w)
{
	size_t	i;

	i = 0;
	while (w)
	{
		w = w->next;
		i++;
	}
	return (i);
}

void			ft_reset_alias(t_envv *alias)
{
	while (alias)
	{
		alias->status = IN;
		alias = alias->next;
	}
}

char			*get_tenvv_val_alias(t_envv *envv, const char *name)
{
	t_envv *tmp;

	if ((tmp = get_tenvv(envv, name)))
	{
		if (tmp->status == AL)
			return (NULL);
		return (tmp->value);
	}
	return (NULL);
}

void			ft_delete_char(t_eval *e)
{
	size_t	i;
	size_t	len;

	i = (size_t)e->curr;
	len = ft_strlen(e->s);
	while (i < len && e->s[e->curr] && e->s[i + 1])
	{
		e->s[i] = e->s[i + 1];
		i++;
	}
	e->s[i] = '\0';
}

char			**ft_twordto_arr(t_word *w)
{
	char	**arr;
	int		i;

	i = 0;
	if (!w || !(arr = malloc(sizeof(char *) * (ft_twordlen(w) + 1))))
		return (NULL);
	while (w)
	{
		if (w->word && ((w->type != NUL && (arr[i] = ft_strdup(w->word)))
				|| (w->type == NUL && (arr[i] = ft_strnew(1)))))
			i++;
		w = w->next;
	}
	if (i == 0)
	{
		free(arr);
		return (NULL);
	}
	if (arr)
		arr[i] = NULL;
	return (arr);
}
