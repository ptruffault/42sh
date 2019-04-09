/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptruffau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/08 13:53:23 by ptruffau          #+#    #+#             */
/*   Updated: 2019/03/26 17:21:55 by stdenis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell42.h"

static int			ft_link_stdin(int pipe[2])
{
	if (dup2(pipe[0], STDIN_FILENO) < 0)
		return (-1);
	return (ft_close(pipe[1]));
}

static int			ft_link_stdout(int pipe[2])
{
	if (dup2(pipe[1], STDOUT_FILENO) < 0)
		return (-1);
	return (ft_close(pipe[0]));
}

static int			ft_close_pipe(int pipe[2])
{
	if (!ft_close(pipe[0])
	|| !ft_close(pipe[1]))
		return (0);
	return (1);
}

static t_process	*ft_stuff(t_process *prev, t_process *tmp, t_shell *sh)
{
	if (prev)
		ft_close_pipe(prev->pipe);
	else
		tmp->pgid = tmp->pid;
	if (sh->interactive == TRUE && setpgid(tmp->pid, tmp->pgid) < 0)
		error("can't set group", tmp->cmd);
	return (tmp);
}

t_tree				*exec_pipe(t_tree *t, t_process *p, t_shell *sh)
{
	t_process	*prev;
	t_process	*tmp;

	prev = NULL;
	tmp = p;
	while (tmp)
	{
		tmp->status = RUNNING_FG;
		if ((tmp->pid = fork()) == 0)
		{
			if ((prev && !ft_link_stdin(prev->pipe))
			|| (tmp->grp && !ft_link_stdout(tmp->pipe)))
				ft_exit_son(sh, -1);
			ft_exec_process(tmp, sh, t);
			ft_exit_son(sh, tmp->ret);
		}
		else if (tmp->pid < 0)
			error("fork fucked up", tmp->cmd);
		else
			prev = ft_stuff(prev, tmp, sh);
		if ((tmp = tmp->grp))
		{
			tmp->pgid = p->pgid;
			t = t->next;
		}
	}
	return (t);
}
