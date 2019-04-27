/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_word_tools.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptruffau <ptruffau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/06 14:18:17 by ptruffau          #+#    #+#             */
/*   Updated: 2019/04/24 16:58:25 by fstadelw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "shell42.h"

static t_word	*ft_cpytword(t_word *src)
{
	t_word	*ret;

	if (!(ret = new_tword()))
		return (NULL);
	ret->type = src->type;
	ret->paste = src->paste;
	if (!(ret->word = ft_strdup(src->word)))
	{
		free(ret);
		return (NULL);
	}
	return (ret);
}

int				check_order_alias(t_word *w, int *doit, int i)
{
	if (*doit == 0 && w->word && ft_strchr(w->word, '='))
		i = 0;
	if (w->type == 2 && *doit > 0)
		i = 1;
	if (w->type == OPERATEUR)
	{
		i = 0;
		*doit = 0;
	}
	return (i);
}

t_word			*ft_deltword(t_word *prev, t_word *src)
{
	if (src && prev)
	{
		prev->next = src->next;
		src->next = NULL;
		src = ft_free_tword(src);
	}
	if (!prev)
		return (src);
	return (prev);
}

t_word			*new_tword(void)
{
	t_word	*n;

	if (!(n = (t_word *)malloc(sizeof(t_word))))
		return (NULL);
	n->word = NULL;
	n->paste = FALSE;
	n->type = undef;
	n->next = NULL;
	return (n);
}

t_word			*ft_addtword(t_word *head, t_word *ret)
{
	t_word	*tmp;

	if (!ret)
		return (head);
	if (!head)
		return (ft_cpytword(ret));
	tmp = head;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = ft_cpytword(ret);
	return (head);
}
