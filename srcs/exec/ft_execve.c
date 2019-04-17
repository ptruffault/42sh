/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptruffau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/08 14:02:44 by ptruffau          #+#    #+#             */
/*   Updated: 2019/03/26 17:21:55 by stdenis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell42.h"

static int		ft_builtins(t_shell *sh, t_process *p, t_tree *t)
{
	if (p->builtins == TRUE)
	{
		if (sh->pid != getpid() && sh->interactive == TRUE)
		{
			p->pid = getpid();
			p->pgid = (p->pgid == 0 ? p->pid : p->pgid);
			if (setpgid(p->pid, p->pgid) < 0)
				error("can't set group", p->cmd);
		}
		p->ret = run_builtin(t, p, sh);
		if (sh->pid != getpid())
			ft_exit_son(sh, p->ret, p);
		return (1);
	}
	return (0);
}

static void		ft_execve(t_process *p, t_shell *sh)
{
	if (sh->interactive == TRUE)
	{
		p->pid = getpid();
		p->pgid = (p->pgid == 0 ? p->pid : p->pgid);
		if (setpgid(p->pid, p->pgid) < 0)
			error("can't set groupmake", p->cmd);
	}
	set_son_signal();
	execve(p->cmd, p->argv, p->env);
	error("execve fucked up", p->cmd);
	ft_exit_son(sh, 1, p);
}

static void		ft_exec(t_process *p, t_shell *sh, t_tree *t)
{
	if (p->builtins == TRUE || check_exe(p->cmd))
	{
		if (p->valid && !ft_builtins(sh, p, t) && (sh->pid != getpid()
			|| (p->pid = fork()) == 0))
			ft_execve(p, sh);
		else if (p->pid < 0)
			error("fork fucked up", p->cmd);
		else
			ft_groups_stuff(sh, p);
	}
	else
		p->ret = 126;
}

t_jobs			*ft_exec_process(t_process *p, t_shell *sh, t_tree *t)
{
	t_jobs *ret;

	ret = NULL;
	if (sh->pid == getpid())
	{
		p->next = sh->process;
		sh->process = p;
		ret = ft_add_jobs(p, sh);
	}
	if (!t->r || ft_redirect_builtin(t, p, sh))
	{
		if (p->cmd && !ft_isempty(p->cmd))
			ft_exec(p, sh, t);
		else
		{
			error("command not found", *p->argv);
			p->ret = 127;
		}
	}
	else
		p->ret = 1;
	ft_get_envv_back(sh, p, t);
	return (ret);
}
