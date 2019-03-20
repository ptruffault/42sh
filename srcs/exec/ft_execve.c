/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptruffau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/08 14:02:44 by ptruffau          #+#    #+#             */
/*   Updated: 2019/03/20 18:11:13 by stdenis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <shell42.h>

void			ft_exit_son(t_tree *t, t_shell *sh, int exit_code)
{
	ft_free_tshell(sh);
	ft_free_tree(t);
	ft_printf("exit ->%i\n", exit_code);
	exit(exit_code);
}

static int		ft_builtins(t_shell *sh, t_process *p, t_tree *t, int frk)
{
	if (p->builtins == TRUE)
	{
		p->ret = run_builtin(t, p->argv, sh);
		if (frk)
			p->pid = 0;
		else
			ft_exit_son(t, sh, p->ret);
		return (1);
	}
	sh->env = ft_new_envv(sh->env, "_", p->cmd);
	return (0);
}

void			ft_execve(t_process *p, t_shell *sh, t_tree *t, int frk)
{
	if (!t->r || ft_redirect_builtin(t, p, sh))
	{
		if (p->cmd && !ft_isempty(p->cmd))
		{
			p->status = (t->o_type == O_BACK ? RUNNING_BG : RUNNING_FG);
			if (!ft_builtins(sh, p, t, frk) && (!frk || (p->pid = fork()) == 0))
			{
				if (frk && t->o_type == O_BACK && setsid() < 0)
					warning("setsid fucked up", p->cmd);
				execve(p->cmd, p->argv, p->env);
				error("execve fucked up", p->cmd);
				ft_exit_son(t, sh, -1);
			}
			else if (p->pid < 0)
				error("fork fucked up", p->cmd);
/*			else if (frk && p->pid > 0 && t->o_type == O_BACK && setpgid(p->pid, 0) != 0)
				warning("can't set pgid on this process", p->cmd);*/
		}
		else
			error("command not found", *p->argv);
	}
}
