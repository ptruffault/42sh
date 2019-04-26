/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_tools.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptruffau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/08 16:10:38 by ptruffau          #+#    #+#             */
/*   Updated: 2019/03/26 17:21:55 by stdenis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell42.h"

int			delete_char_j(int j, char *ret)
{
	while (ret[j++])
		ret[j - 1] = ret[j];
	return (j);
}

int			checktilde(t_word *w)
{
	struct passwd	*usr;
	char			*tmp;

	if (w->word[1] == '/' || w->word[1] == '\0')
		return (1);
	if ((usr = getpwnam(&w->word[1])) != NULL)
	{
		tmp = w->word;
		if ((w->word = ft_strdup(usr->pw_dir)))
			ft_strdel(&tmp);
		else
			w->word = tmp;
		return (0);
	}
	return (0);
}
