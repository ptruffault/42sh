/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptruffau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/08 14:09:28 by ptruffau          #+#    #+#             */
/*   Updated: 2019/03/26 17:21:55 by stdenis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell42.h"

static void	ft_heredoc_content(t_redirect *r, t_shell *sh)
{
	int fd[2];

	(void)sh;
	if (pipe(fd) == 0)
	{
		ft_putstr_fd(r->heredoc, fd[1]);
		ft_close(fd[1]);
		r->to = fd[0];
		r->from = STDIN_FILENO;
	}
}

int ft_isstd(int i)
{
	if (0 <= i && i <= 2)
		return (1);
	return (0);
}

int			fd_dup(int fd1, int fd2, t_process *p)
{
	int		ret;
	t_shell	*sh;

	sh = ft_get_set_shell(NULL);
	if ((ft_isstd(fd1) && (p->fd[fd1] == -1)))
		return (error_i("bad file descriptor", fd1) - 1);
	else if (!ft_isstd(fd1) && ft_isstd(fd2) && fd1 == sh->std[fd2])
		return (error_i("bad file descriptor", fd1) - 1);
	ret = 0;
	if (fd1 != -1)
	{
		if ((ret = dup2(fd1, fd2)) < 0)
			return (error_i("duplicate file descriptor fucked up", fd1) - 1);
		if (!ft_isstd(fd1))
			ft_close(fd1);
		if (!ft_isstd(fd2))
			ft_close(fd2);
	}
	return (ret);
}

int			get_destination_fd(t_redirect *r)
{
	r->path = ft_exp_var(r->path, ft_get_set_shell(NULL));
	if ((r->t == R_RIGHT && r->to == -2 && r->path
			&& (r->to = ft_open(r->path
			, O_RDWR | O_TRUNC | O_CREAT, 0644)) < 0)
		|| (r->t == R_DRIGHT && r->to == -2 && r->path
			&& (r->to = ft_open(r->path
			, O_RDWR | O_APPEND | O_CREAT, 0644)) < 0)
		|| (r->t == R_LEFT && r->to == -2 && r->path
			&& (r->to = ft_open(r->path, O_RDWR, 0644)) < 0))
		return (0);
	else if (r->t == R_DLEFT)
		ft_heredoc_content(r, ft_get_set_shell(NULL));
	if (r->to != -2 && r->from != -2)
		return (1);
	return (0);
}
