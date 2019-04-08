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

static void	ft_fc_write_in_file(t_fc *fc, int fd)
{
	t_hist	*tmp;
	int		way;

	if (ft_strchr(fc->flags, 'r'))
	{
		tmp = fc->hist_first;
		fc->hist_first = fc->hist_last;
		fc->hist_last = tmp;
	}
	way = fc->hist_first->nb < fc->hist_last->nb ? 1 : 0;
	if (way == 0)
		while (fc->hist_first->nb >= fc->hist_last->nb)
		{
			ft_putendl_fd(fc->hist_first->s, fd);
			fc->hist_first = fc->hist_first->next;
		}
	else if (way == 1)
		while (fc->hist_first->nb <= fc->hist_last->nb)
		{
			ft_putendl_fd(fc->hist_first->s, fd);
			fc->hist_first = fc->hist_first->prev;
		}
}

void		ft_fc_option_e(t_fc *fc, int pos)
{
	char	*editor;
	int		fd;
	char	*tmp;
	t_tree	*t;

	editor = NULL;
	if (fc->av[pos] && !ft_isdigit(fc->av[pos][0]) && fc->av[pos][0] != '-')
		editor = fc->av[pos];
	else if (!(editor = get_tenvv_val(fc->shell->env, "FCEDIT")))
		return ;
	else if (editor == NULL)
		if (!(editor = ft_strdup("ed")))
			return ;
	if (search_in_hist_parser(fc, 3) == FAILURE)
		return ;
	if (!(tmp = ft_strjoin(editor, " /tmp/fc____42sh")))
		return ;
	ft_strdel(&editor);
	editor = tmp;
	if ((fd = open("/tmp/fc____42sh", O_CREAT | O_RDWR, 0644)) == -1)
		return ;
	ft_fc_write_in_file(fc, fd);
	ft_strdel(&fc->shell->hist->s);
	close(fd);
	fc->shell->hist->s = editor;
	if ((t = get_tree(editor)))
		ft_free_tree(exec_tree(t, fc->shell));
	fd = open("/tmp/fc____42sh", O_RDWR, 0644);
	exec_fd(fc->shell, fd);
	unlink("/tmp/fc____42sh");
	close(fd);
}
