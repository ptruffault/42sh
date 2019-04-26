/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_input.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptruffau <ptruffau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/13 13:12:58 by ptruffau          #+#    #+#             */
/*   Updated: 2019/04/24 17:26:16 by fstadelw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "shell42.h"
#include "get_input.h"

static int	replace_first_link(t_shell *sh)
{
	t_hist *hist;

	hist = sh->e.hist;
	while (hist->prev)
		hist = hist->prev;
	ft_strdel(&hist->s);
	if (!(hist->s = ft_strdup(sh->e.hist->s)))
	{
		free(hist);
		return (FAILURE);
	}
	sh->e.hist = hist;
	sh->hist = sh->e.hist;
	return (SUCCESS);
}

static void	ft_update_with_heredoc(t_shell *sh)
{
	if (sh->e.hist && sh->e.hist->next)
	{
		sh->e.hist = sh->e.hist->next;
		ft_strdel(&sh->e.hist->prev->s);
		free(sh->e.hist->prev);
		sh->e.hist->prev = NULL;
	}
	else if (sh->e.hist)
	{
		ft_strdel(&sh->e.hist->s);
		free(sh->e.hist);
		sh->hist = NULL;
	}
}

static int	ft_update_hist(t_shell *sh)
{
	if (!sh->heredoc && sh->e.hist
		&& sh->e.hist->s && !ft_isempty(sh->e.hist->s))
	{
		if (!sh->e.hist->prev)
			sh->hist = sh->e.hist;
		else if (replace_first_link(sh) == FAILURE)
			return (FAILURE);
		ft_print_edited(&sh->e);
	}
	else if (!sh->heredoc && sh->e.hist && !ft_isempty(sh->e.hist->s))
	{
		while (sh->e.hist->prev)
			sh->e.hist = sh->e.hist->prev;
		ft_strdel(&sh->e.hist->s);
		sh->e.hist = sh->e.hist->next;
		if (sh->e.hist && sh->e.hist->prev)
		{
			free(sh->e.hist->prev);
			sh->e.hist->prev = NULL;
		}
	}
	else if (sh->e.hist && (sh->heredoc || ft_isempty(sh->e.hist->s)))
		ft_update_with_heredoc(sh);
	return (ft_set_old_term(sh, SUCCESS));
}

int			get_input(char **line)
{
	t_shell			*sh;
	unsigned long	buf;

	sh = ft_get_set_shell(NULL);
	if (!isatty(0) || sh->interactive == FALSE || !init_tedit(sh)
		|| !ft_setup_edit_term(sh))
		return (FAILURE);
	buf = 0;
	sh->e.head = sh->e.hist;
	while (sh->e.edited == FALSE && read(0, &buf, 8) > 0)
	{
		buf = (unsigned int)handle_input(buf, &sh->e);
		if (buf == 9)
			return (ft_set_old_term(sh, 4));
		else if (buf == 10 && (!sh->e.hist
				|| !sh->e.hist->s || !*sh->e.hist->s))
			return (ft_set_old_term(sh, 0));
		if (sh->e.hist && sh->e.hist->s)
			ft_print_line(&sh->e);
		buf = 0;
	}
	if (sh->e.hist)
		*line = ft_strdup(sh->e.hist->s);
	return (ft_update_hist(sh));
}
