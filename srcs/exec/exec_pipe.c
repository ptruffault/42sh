/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptruffau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/08 13:53:23 by ptruffau          #+#    #+#             */
/*   Updated: 2019/03/19 19:04:57 by stdenis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <shell42.h>

static void		ft_link_stdin(int pipe[2])
{
	dup2(pipe[0], STDIN_FILENO);
	ft_close(pipe[1]);
}

static void		ft_link_stdout(int pipe[2])
{
	dup2(pipe[1], STDOUT_FILENO);
	ft_close(pipe[0]);
}

static int		ft_close_pipe(int pipe[2])
{
	if (!ft_close(pipe[0])
	|| !ft_close(pipe[1]))
		return (0);
	return (1);
}

/* 
static void		ft_exec_son(t_process *p, t_tree *t, t_shell *sh)
{
	int exit_code;

	exit_code = -1;
	if (!t->r || (t->r && ft_redirect_builtin(t, p, sh)))
	{
		if (p->builtins == TRUE)
			exit_code = run_builtin(t, p->argv, sh);
		else if (p->cmd && !ft_isempty(p->cmd))
		{
			execve(p->cmd, p->argv, p->env);
			error("execve fucked up", p->cmd);
		}
		else
			error("command not found", *p->argv);
	}
	ft_free_tshell(sh);
	ft_free_tree(t);
	exit(exit_code);
}*/


t_tree			*exec_pipe(t_tree *t, t_process *p, t_shell *sh)
{
	t_process	*prev;
	t_process	*tmp;

	prev = NULL;
	tmp = p;
	while (tmp)
	{
		tmp->status = RUNNING_FG;
		if (tmp->cmd && (tmp->pid = fork()) == 0)
		{
			if (prev)
				ft_link_stdin(prev->pipe);
			if (tmp->grp)
				ft_link_stdout(tmp->pipe);
			ft_execve(tmp, sh, t, 0);
		}
	/*	if ((!prev && (setpgid(tmp->pid, 0)) < 0)
		|| (prev && setpgid(tmp->pid, p->pid) < 0))
		{
			warning("can't set pgid", tmp->cmd);
			perror(tmp->cmd);
		}*/

		if (prev)
			ft_close_pipe(prev->pipe);
		prev = tmp;
		tmp = tmp->grp;
		t = t->next;
	}
	ft_wait(p, sh);
	ft_reset_fd(sh);
	return (t);
}

