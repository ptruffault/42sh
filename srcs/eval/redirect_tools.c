/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_tools.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptruffau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/25 16:13:25 by ptruffau          #+#    #+#             */
/*   Updated: 2019/04/25 16:13:26 by ptruffau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell42.h"

t_word				*ft_delete_redir_stuff(t_word *w)
{
	t_bool paste;

	if (w->next && w->next->paste)
	{
		w = w->next;
		paste = w->paste;
		while (w->next && paste)
		{
			paste = w->next->paste;
			w = ft_deltword(w, w->next);
		}
	}
	else
		w = ft_deltword(w, w->next);
	return (w);
}

char				*ft_get_redir_path(t_word *w)
{
	char *ret;
	char *tmp;

	if (!(ret = ft_strdup(w->word)))
		return (NULL);
	tmp = ret;
	while (w->next && w->paste)
	{
		if (!(tmp = ft_strappend(&ret, w->next->word)))
		{
			ft_strdel(&ret);
			return (NULL);
		}
		ret = tmp;
		w = w->next;
	}
	return (ret);
}
