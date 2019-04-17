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

static void	fc_option_e_stuff(t_fc *fc)
{
	ft_strdel(&fc->shell->txt);
	ft_strdel(&fc->shell->hist->s);
	fc->shell->hist->s = ft_strnew(3);
	fc->shell->interactive = FALSE;
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
	fc_option_e_stuff(fc);
	exec_file("/tmp/fc____42sh", fc->shell);
	fc->shell->interactive = TRUE;
	fc->shell->fc = FALSE;
	unlink("/tmp/fc____42sh");
	return (fc_free_editor(editor));
}
