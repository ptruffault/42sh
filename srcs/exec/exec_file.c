/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptruffau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/08 13:59:48 by ptruffau          #+#    #+#             */
/*   Updated: 2019/03/26 17:21:55 by stdenis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell42.h"

char	*join_or_save_txt(char *tmp, t_shell *sh)
{
	if (tmp == NULL)
		return (sh->txt);
	tmp = ft_strjoin_add_if(&tmp, &sh->txt, "\n");
	sh->txt = tmp;
	return (tmp);
}

static void	tree_fill(t_shell *sh, int x)
{
	t_tree *t;
	if (*sh->txt != '#' && (t = get_tree(sh->txt)))
		ft_free_tree(exec_tree(t, sh));
	if (sh->fc == TRUE)
		read_from_add_to_hist(sh, sh->txt, x);
	ft_strdel(&sh->txt);
}

int		exec_fd(t_shell *sh, int fd)
{
	int		i;
	t_eval	eval;
	char	*tmp;
	int		x;

	i = 0;
	tmp = NULL;
	sh->fd = fd;
	x = 0;
	while (get_next_line(sh->fd, &sh->txt) == 1 && !ft_isempty(sh->txt))
	{
		tmp = join_or_save_txt(tmp, sh);
		lexer(&eval, sh->txt);
		ft_strdel(&eval.eval);
		ft_strdel(&eval.s);
		if (eval.err == 0)
		{
			tree_fill(sh, x++);
			tmp = NULL;
		}
		i++;
	}
	ft_strdel(&sh->txt);
	ft_strdel(&tmp);
	return (i);
}

int		exec_file(char *path, t_shell *sh)
{
	int fd;

	if ((fd = ft_open(path, O_RDWR, S_IRUSR | S_IXUSR)) >= 0)
	{
		exec_fd(sh, fd);
		ft_close(fd);
	}
	else
		return (-1);
	return (0);
}
