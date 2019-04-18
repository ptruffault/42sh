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
	return (close(fd));
}

static int	fc_option_e_stuff(t_fc *fc, char *editor)
{
	t_tree	*t;

	if ((t = get_tree(editor, fc->shell)))
	{
		t = exec_tree(t, fc->shell);
		if (t->ret != 0)
		{
			ft_free_tree(t);
			return (1);
		}
		ft_free_tree(t);
	}
	else
		return (1);
	ft_strdel(&fc->shell->txt);
	ft_strdel(&fc->shell->hist->s);
	fc->shell->hist->s = ft_strnew(3);
	fc->shell->interactive = FALSE;
	return (0);
}

int			ft_fc_option_e(t_fc *fc, int pos)
{
	char	*editor;

	editor = NULL;
	if (search_in_hist_parser(fc, 3) == FAILURE)
		return (1);
	if (fc->av[pos] && !ft_isdigit(fc->av[pos][0]) && fc->av[pos][0] != '-')
		editor = ft_strdup(fc->av[pos]);
	else if (!(editor = ft_strdup(get_tenvv_val(fc->shell->env, "FCEDIT")))
			&& (editor == NULL && !(editor = ft_strdup("ed"))))
		return (1);
	if (!(editor = ft_strappend(&editor, FCTMPEXEC)))
		return (fc_free_editor(editor));
	if (ft_fc_write_in_file(fc, open(FCTMP, O_CREAT | O_RDWR, 0644)))
		return (fc_free_editor(editor) + 1);
	fc->shell->fc = TRUE;
	if ((fc_option_e_stuff(fc, editor)))
		return (fc_free_editor(editor) + 1);
	exec_file(FCTMP, fc->shell);
	fc->shell->interactive = TRUE;
	fc->shell->fc = FALSE;
	unlink(FCTMP);
	return (fc_free_editor(editor));
}
