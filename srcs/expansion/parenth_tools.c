/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parenth_tools.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptruffau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/18 15:43:53 by ptruffau          #+#    #+#             */
/*   Updated: 2019/03/26 17:21:55 by stdenis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell42.h"

char	*ft_get_secondvalue(char *src)
{
	char	*cpy;
	char	*ret;
	int		i;

	i = 0;
	ret = NULL;
	if (src && (cpy = ft_strdup(src)))
	{
		while (cpy && cpy[i] && cpy[i] != '#' && cpy[i] != '%' &&
		(i == 0 || cpy[i - 1] != '}'))
			i++;
		if (cpy && !(ret = ft_strndup(cpy, i)))
			return (ft_strdell(&cpy));
		ft_strdel(&cpy);
	}
	return (ret);
}

int		get_content_size(char *s)
{
	int i;

	i = 2;
	if (!s)
		return (0);
	while (s[i] && s[i] != '}')
	{
		if (s[i] == '$' && s[i + 1] == '{')
			i = i + get_content_size(&s[i]) + 2;
		i++;
	}
	return (i - 2);
}

t_tree	*ft_word_paste(t_tree *t)
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
