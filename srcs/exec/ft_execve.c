/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptruffau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/08 14:02:44 by ptruffau          #+#    #+#             */
/*   Updated: 2019/03/19 19:04:57 by stdenis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <shell42.h>

static void	ft_free_all_and_exit(t_tree *t, t_shell *sh)
{
	ft_free_tshell(sh);
	ft_free_tree(t);
	exit(-1);
}

static int		ft_builtins(t_shell *sh, t_process *p, t_tree *t, int frk)
{
	if (p->builtins == TRUE)
	{
		p->ret = run_builtin(t, p->argv, sh);
		if (frk)
			p->pid = 0;
		else
			ft_free_all_and_exit(t, sh);
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
				execve(p->cmd, p->argv, p->env);
				ft_free_all_and_exit(t, sh);
			}
			else if (p->pid < 0)
				error("fork fucked up", p->cmd);
		}
		else
			error("command not found", *p->argv);
	}
	if (!frk)
		ft_free_all_and_exit(t, sh);
}
