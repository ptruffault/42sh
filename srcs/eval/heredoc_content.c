/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_content.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adi-rosa <adi-rosa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/08 14:15:32 by adi-rosa          #+#    #+#             */
/*   Updated: 2019/04/24 16:54:55 by fstadelw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "shell42.h"

static char		*heredoc_get_input(char *eoi, t_shell *sh)
{
	char	*ret;
	char	*in;
	int		d;

	if (!eoi || !(ret = ft_strnew(0)))
		return (NULL);
	in = NULL;
	ft_others_prompt(sh, "heredoc");
	if ((d = get_input(&in)) != 4)
		while (!ft_strequ(in, eoi) && sh->heredoc == 1)
		{
			if (!(in = ft_stradd(&in, "\n"))
				|| !(ret = ft_strappend_fr(&ret, &in)))
				break ;
			ft_others_prompt(sh, "\nheredoc");
			if ((d = get_input(&in)) == 4)
			{
				ft_strdel(&in);
				ft_strdel(&ret);
				return (NULL);
			}
		}
	ft_strdel(&in);
	write(0, "\n", 1);
	return (ret);
}

static char		*heredoc_get_content(char *eof, t_shell *sh)
{
	char *ret;
	char *line;

	ret = NULL;
	if (!eof)
		return (ret);
	while (get_next_line(sh->fd, &line) == 1)
	{
		if (!ft_strequ(line, eof))
			ret = ft_strjoin_fr(ret, ft_stradd_char(line, '\n'));
		else
		{
			ft_strdel(&line);
			break ;
		}
	}
	if ((sh->txt = ft_stradd_char(sh->txt, '\n')))
		sh->txt = ft_strappend(&sh->txt, ret);
	return (ret);
}

static t_word	*get_eof_pasted(t_word *ret, t_word *w, char **str)
{
	char	*tmp;

	if (w->type == QUOTE)
		ret->type = QUOTE;
	while (w->next && w->paste)
	{
		if (!(tmp = ft_strappend(str, w->next->word)))
		{
			ft_strdel(str);
			return (ft_free_tword(ret));
		}
		tmp = *str;
		if (w->type == QUOTE)
			ret->type = QUOTE;
		w = w->next;
	}
	return (ret);
}

static t_word	*ft_heredoc_eof(t_word *w)
{
	t_word	*ret;
	char	*str;

	if (!(ret = new_tword()))
		return (NULL);
	if (!(str = ft_strdup(w->word)))
		return (ft_free_tword(ret));
	ret->type = w->type;
	if (w->paste)
		ret = get_eof_pasted(ret, w, &str);
	if (ret && !(ret->word = ft_strdup_trim(str)))
	{
		ft_strdel(&str);
		return (ft_free_tword(ret));
	}
	ft_strdel(&str);
	return (ret);
}

t_redirect		*parse_heredoc(t_redirect *ret, t_word *w)
{
	t_shell *sh;

	sh = ft_get_set_shell(NULL);
	ret->from = STDIN_FILENO;
	if (w->next && w->next->word)
	{
		if (!(ret->eof = ft_heredoc_eof(w->next)))
			return (ft_free_redirection(ret));
		sh->heredoc = 1;
		if (sh->interactive == TRUE)
			ret->heredoc = heredoc_get_input(ret->eof->word, sh);
		else
			ret->heredoc = heredoc_get_content(ret->eof->word, sh);
		if (ret->eof->type != QUOTE)
		{
			ret->heredoc = ft_exp_var(ret->heredoc, sh, FALSE);
			ret->heredoc = ft_clear_backslash(ret->heredoc);
		}
		sh->heredoc = 0;
		return (ret);
	}
	return (ft_free_redirection(ret));
}
