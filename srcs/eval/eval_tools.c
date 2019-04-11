/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eval_tools.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptruffau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/07 14:19:48 by ptruffau          #+#    #+#             */
/*   Updated: 2019/03/26 17:21:55 by stdenis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell42.h"

int			ft_twordlen(t_word *w)
{
	int	i;

	i = 0;
	while (w)
	{
		w = w->next;
		i++;
	}
	return (i);
}

void		ft_delete_char(t_eval *e)
{
	int i;
	int len;

	i = e->curr;
	len = ft_strlen(e->s);
	while (i < len && e->s[e->curr] && e->s[i + 1])
	{
		e->s[i] = e->s[i + 1];
		i++;
	}
	e->s[i] = '\0';
}

char		**ft_twordto_arr(t_word *w)
{
	char	**arr;
	int		i;

	i = 0;
	if (!w || !(w = ft_expention(w)))
		return (NULL);
	if (!(arr = malloc(sizeof(char *) * (ft_twordlen(w) + 1))))
		return (NULL);
	while (w)
	{
		if (w->word && ft_strchr(w->word, 6)
			&& (arr[i] = ft_strnew(0)))
			i++;
		else if (w->word && (arr[i] = ft_strdup(w->word)))
		{
			while (w->paste == TRUE && w->next && w->next->word)
			{
				w = w->next;
				if (w->word && !ft_strchr(w->word, 6)
				&& !(arr[i] = ft_strappend(&arr[i], w->word)))
					return (ft_delstrarr(&arr));
			}
			i++;
		}
		w = (w ? w->next : w);
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
