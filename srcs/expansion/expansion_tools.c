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

int			checktilde(t_word *w)
{
	struct passwd	*usr;

	if (w->word[1] == '/' || w->word[1] == '\0')
		return (1);
	if ((usr = getpwnam(&w->word[1])) != NULL)
	{
		ft_strdel(&w->word);
		w->word = ft_strdup(usr->pw_dir);
		return (0);
	}
	return (0);
}
