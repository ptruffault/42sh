/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_tools.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptruffau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/16 11:05:14 by ptruffau          #+#    #+#             */
/*   Updated: 2019/04/16 11:05:15 by ptruffau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

int			ft_link_stdin(int pipe[2])
{
	if (dup2(pipe[0], STDIN_FILENO) < 0)
		return (-1);
	ft_close(pipe[0]);
	return (ft_close(pipe[1]));
}

int			ft_link_stdout(int pipe[2])
{
	if (dup2(pipe[1], STDOUT_FILENO) < 0)
		return (-1);
	ft_close(pipe[1]);
	return (ft_close(pipe[0]));
}

int			ft_close_pipe(int pipe[2])
{
	if (!ft_close(pipe[0])
	|| !ft_close(pipe[1]))
		return (0);
	return (1);
}
