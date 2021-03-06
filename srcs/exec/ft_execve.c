/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execve.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptruffau <ptruffau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/08 14:02:44 by ptruffau          #+#    #+#             */
/*   Updated: 2019/04/24 16:51:18 by fstadelw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <signal.h>
#include "shell42.h"
#include "ft_printf.h"

static int		ft_builtins(t_shell *sh, t_process *p, t_tree *t)
{
	if (p->builtins == TRUE)
	{
		if (sh->pid != getpid() && sh->interactive == TRUE)
		{
			p->pid = getpid();
			if (setpgid(p->pid, p->pgid) < 0)
				error("group creation fucked up", p->cmd);
		}
		signal(SIGINT, sig_handler);
		if ((t->r && ft_redirect_builtin(t, p, sh)) || !t->r)
			p->ret = run_builtin(t, p, sh);
		else
			p->ret = 1;
		if (sh->pid != getpid())
			ft_exit_son(sh, p->ret, p);
		return (1);
	}
	return (0);
}

static void		ft_execve(t_process *p, t_shell *sh, t_tree *t)
{
	if (sh->interactive == TRUE)
	{
		p->pid = getpid();
		if (setpgid(p->pid, p->pgid) < 0)
			error("group creation fucked up", p->cmd);
	}
	set_son_signal();
	if ((t->r && ft_redirect_builtin(t, p, sh)) || !t->r)
	{
		execve(p->cmd, p->argv, p->env);
		error("execve fucked up", p->cmd);
	}
	ft_exit_son(sh, 1, p);
}

static void		ft_exec(t_process *p, t_shell *sh, t_tree *t)
{
	if (p->builtins == TRUE || check_exe(p->cmd))
	{
		if (p->valid && !ft_builtins(sh, p, t) && (sh->pid != getpid()
				|| (p->pid = fork()) == 0))
			ft_execve(p, sh, t);
		else if (p->pid < 0)
		{
			error("fork fucked up", p->cmd);
			p->ret = 1;
		}
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
	if (p->cmd && !ft_isempty(p->cmd))
		ft_exec(p, sh, t);
	else
	{
		p->ret = 127;
		if (getpid() == sh->pid
			&& ((t->r && ft_redirect_builtin(t, p, sh)) || !t->ret))
			error("command not found", *p->argv);
	}
	ft_get_envv_back(sh, p, t);
	return (ret);
}
