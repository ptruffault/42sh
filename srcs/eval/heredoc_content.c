/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adi-rosa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/08 14:15:32 by adi-rosa          #+#    #+#             */
/*   Updated: 2019/03/26 17:21:55 by stdenis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell42.h"

static char		*ft_heredoc_clear(char *in, char *ret)
{
	ft_strdel(&in);
	ft_strdel(&ret);
	return (NULL);
}

static char		*heredoc_get_input(char *eoi, t_shell *sh)
{
	char	*ret;
	char	*in;
	t_hist	*hist;
	int		d;

	if (!(ret = ft_strnew(0)))
		return (NULL);
	in = NULL;
	hist = sh->e.hist;
	ft_others_prompt(sh, "heredoc");
	if ((d = get_input(&in)) != 4)
		while (!ft_strequ(in, eoi) && sh->heredoc == 1)
		{
			if (!(in = ft_stradd(&in, "\n"))
				|| !(ret = ft_strappend_fr(&ret, &in)))
				break ;
			ft_others_prompt(sh, "\nheredoc");
			if ((d = get_input(&in)) == 4)
				return (ft_heredoc_clear(in, ret));
		}
	ft_strdel(&in);
	hist->s = ft_stradd_char(hist->s, '\n');
	hist->s = ft_strappend(&hist->s, ret);
	return (ret);
}

static char		*heredoc_get_content(char *eof, t_shell *sh)
{
	char *ret;
	char *line;

	ret = NULL;
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
	sh->txt = ft_stradd_char(sh->txt, '\n');
	sh->txt = ft_strappend(&sh->txt, ret);
	return (ret);
}

t_redirect		*parse_heredoc(t_redirect *ret, t_word *w)
{
	t_shell *sh;

	sh = ft_get_set_shell(NULL);
	if (w->next && w->next->word)
	{
		if (!(ret->path = ft_strdup_trim(w->next->word)))
			return (ft_free_redirection(ret));
		sh->heredoc = 1;
		if (sh->interactive == TRUE)
			ret->heredoc = heredoc_get_input(ret->path, sh);
		else
			ret->heredoc = heredoc_get_content(ret->path, sh);
		sh->heredoc = 0;
		return (ret);
	}
	return (ft_free_redirection(ret));
}
