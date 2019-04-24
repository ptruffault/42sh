/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fc_free_editor.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adi-rosa <adi-rosa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/16 13:34:56 by adi-rosa          #+#    #+#             */
/*   Updated: 2019/04/24 17:03:41 by fstadelw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "shell42.h"

int			fc_free_editor(char *editor)
{
	ft_strdel(&editor);
	return (0);
}

static int	get_from_last(t_hist *hist, char *line, t_shell *sh)
{
	hist = sh->hist;
	while (hist->next)
		hist = hist->next;
	hist->prev->next = NULL;
	hist->prev = NULL;
	hist->next = sh->hist;
	sh->hist->prev = hist;
	hist->nb = sh->hist->nb + 1;
	ft_strdel(&hist->s);
	hist->s = line;
	sh->hist = hist;
	return (SUCCESS);
}

static int	add_to_hist(char *line, t_shell *sh, int hist_size)
{
	t_hist *hist;

	if (!line)
		return (FAILURE);
	hist = NULL;
	if (sh->hist && hist_size <= sh->hist->nb)
		return (get_from_last(hist, line, sh));
	if (!(hist = new_hist()))
		return (FAILURE);
	if (sh->hist)
		sh->hist->prev = hist;
	hist->next = sh->hist ? sh->hist : NULL;
	hist->s = line;
	hist->nb = sh->hist ? sh->hist->nb + 1 : 1;
	sh->hist = hist;
	return (SUCCESS);
}

int			read_from_add_hist(t_shell *sh, char *line, int x)
{
	int nb;

	nb = ft_get_hist_size();
	if (x == 0)
	{
		ft_strdel(&sh->hist->s);
		if (!(sh->hist->s = ft_strdup(line)))
		{
			if (sh->hist->next)
			{
				sh->hist = sh->hist->next;
				free(sh->hist->prev);
				sh->hist->prev = NULL;
			}
			return (FAILURE);
		}
	}
	else if (x != 0 && add_to_hist(ft_strdup(line), sh, nb) == FAILURE)
		return (FAILURE);
	return (SUCCESS);
}
