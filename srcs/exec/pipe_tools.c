/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_tools.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptruffau <ptruffau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/16 11:05:14 by ptruffau          #+#    #+#             */
/*   Updated: 2019/04/24 16:52:54 by fstadelw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "shell42.h"

void		ft_groups_stuff(t_shell *sh, t_process *p)
{
	if (sh->interactive == TRUE && sh->pid == getpid())
	{
		p->pgid = (p->pgid == 0 ? p->pid : p->pgid);
		if (setpgid(p->pid, p->pgid) < 0)
			error("can't set group (parent)", p->cmd);
	}
}

void		ft_close_pipe(int pipe[2])
{
	if (pipe[0] != -1)
		ft_close(pipe[0]);
	if (pipe[1] != -1)
		ft_close(pipe[1]);
}

int			ft_link_stdin(t_process *p)
{
	if ((p->fd[0] = dup2(p->pipe[0], STDIN_FILENO)) < 0)
		return (-1);
	ft_close_pipe(p->pipe);
	return (1);
}

int			ft_link_stdout(t_process *p)
{
	if ((p->fd[1] = dup2(p->pipe[1], STDOUT_FILENO)) < 0)
		return (-1);
	ft_close_pipe(p->pipe);
	return (1);
}
