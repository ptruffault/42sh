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

int add_to_hist(char *line, t_shell *sh, int hist_size)
{
	t_hist *hist;

	if (sh->hist && hist_size <= sh->hist->nb)
	{
		hist = sh->hist;
		while (hist->next)
			hist = hist->next;
		hist->prev->next = NULL;
		hist->prev = NULL;
		hist->next = sh->hist;
		sh->hist->prev = hist;
		hist->nb = sh->hist->nb + 1;
		hist->s = line;
		return (SUCCESS);
	}
	if (!(hist = new_hist()))
	{
		free(hist);
		return (FAILURE);
	}
	if (sh->hist)
		sh->hist->prev = hist;
	hist->next = sh->hist ? sh->hist : NULL;
	hist->s = line;
	sh->hist = hist;
	return (SUCCESS);
}

int read_from_add_hist(char *file, t_shell *sh, t_fc *fc)
{
	int		fd;
	char	*line;
	int		x;

	if ((fd = open(file, O_RDONLY)) == -1)
		return (error("Could not open the file", file));
	fc->hist_size = ft_get_hist_size();
	x = 0;
	while (get_next_line(fd, &line) > 0)
	{
		if (x == 0)
		{
			ft_strdel(&sh->hist->s);
			sh->hist->s = line;
		}
		else if (x != 0 && add_to_hist(line, sh, fc->hist_size) == FAILURE)
			return (FAILURE);
		line = NULL;
		++x;
	}
	return (SUCCESS);
}

void		ft_fc_option_e(t_fc *fc, int pos)
{
	char	*editor;
	int		fd;
	char	*tmp;
	t_tree	*t;

	editor = NULL;
	if (fc->av[pos] && !ft_isdigit(fc->av[pos][0]) && fc->av[pos][0] != '-')
		editor = ft_strdup(fc->av[pos]);
	else if (!(editor = ft_strdup(get_tenvv_val(fc->shell->env, "FCEDIT")))
			|| (editor == NULL && !(editor = ft_strdup("ed"))))
		return ;
	if (search_in_hist_parser(fc, 3) == FAILURE)
		return ;
	if (!(tmp = ft_strjoin(editor, " /tmp/fc____42sh")))
		return ;
	ft_strdel(&editor);
	if ((fd = open("/tmp/fc____42sh", O_CREAT | O_RDWR, 0644)) == -1)
		return ;
	ft_fc_write_in_file(fc, fd);
	close(fd);
	if ((t = get_tree(tmp)))
		ft_free_tree(exec_tree(t, fc->shell));
	ft_strdel(&tmp);
	if (fc->shell->txt)
		ft_printf("\n%s\n", fc->shell->txt);
	ft_strdel(&fc->shell->txt);
	exec_file("/tmp/fc____42sh", fc->shell);
	read_from_add_hist("/tmp/fc____42sh", fc->shell, fc);
	unlink("/tmp/fc____42sh");
}
