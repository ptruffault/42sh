/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fc_option_e.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adi-rosa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/01 16:07:42 by adi-rosa          #+#    #+#             */
/*   Updated: 2019/04/01 16:07:42 by adi-rosa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell42.h"

static int	ft_fc_write_in_file(t_fc *fc, int fd)
{
	t_hist	*tmp;
	int		way;

	if (fd < 0)
		return (1);
	if (ft_strchr(fc->flags, 'r'))
	{
		tmp = fc->hist_first;
		fc->hist_first = fc->hist_last;
		fc->hist_last = tmp;
	}
	way = fc->hist_first->nb < fc->hist_last->nb ? 1 : 0;
	if (way == 0 && fc->hist_first && fc->hist_last)
		while (fc->hist_first && fc->hist_first->nb >= fc->hist_last->nb)
		{
			ft_putendl_fd(fc->hist_first->s, fd);
			fc->hist_first = fc->hist_first->next;
		}
	if (way == 1 && fc->hist_first && fc->hist_last)
		while (fc->hist_first && fc->hist_first->nb <= fc->hist_last->nb)
		{
			ft_putendl_fd(fc->hist_first->s, fd);
			fc->hist_first = fc->hist_first->prev;
		}
	close(fd);
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

int			ft_fc_option_e(t_fc *fc, int pos)
{
	char	*editor;
	t_tree	*t;

	editor = NULL;
	if (search_in_hist_parser(fc, 3) == FAILURE)
		return (0);
	if (fc->av[pos] && !ft_isdigit(fc->av[pos][0]) && fc->av[pos][0] != '-')
		editor = ft_strdup(fc->av[pos]);
	else if (!(editor = ft_strdup(get_tenvv_val(fc->shell->env, "FCEDIT")))
			|| (editor == NULL && !(editor = ft_strdup("ed"))))
		return (0);
	if (!(editor = ft_strappend(&editor, " /tmp/fc____42sh")))
		return (fc_free_editor(editor));
	if (ft_fc_write_in_file(fc, open("/tmp/fc____42sh"
		, O_CREAT | O_RDWR, 0644)))
		return (fc_free_editor(editor));
	fc->shell->fc = TRUE;
	if ((t = get_tree(editor, fc->shell)))
		ft_free_tree(exec_tree(t, fc->shell));
	ft_strdel(&fc->shell->txt);
	ft_strdel(&fc->shell->hist->s);
	fc->shell->hist->s = ft_strnew(3);
	fc->shell->interactive = FALSE;
	exec_file("/tmp/fc____42sh", fc->shell);
	fc->shell->interactive = TRUE;
	unlink("/tmp/fc____42sh");
	return (fc_free_editor(editor));
}
