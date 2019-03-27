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

void			ft_exit_son(t_shell *sh, int exit_code)
{
	ft_free_tshell(sh);
	ft_free_tree(ft_get_set_tree(NULL));
	exit(exit_code);
}

static int		ft_builtins(t_shell *sh, t_process *p, t_tree *t, int frk)
{
	if (p->builtins == TRUE)
	{
		p->ret = run_builtin(t, p->argv, sh);
		if (!frk)
			ft_exit_son(sh, p->ret);
		return (1);
	}
	return (0);
}


t_process		*ft_execve(t_process *p, t_shell *sh, t_tree *t, int frk)
{
	if (p && (!t->r || ft_redirect_builtin(t, p, sh)))
	{
		if (p->cmd && !ft_isempty(p->cmd))
		{
			if (!ft_builtins(sh, p, t, frk) && (!frk || (p->pid = fork()) == 0))
			{
				if (p->background == TRUE)
				{
					ft_printf("here i am");
					setsid();
				}
				execve(p->cmd, p->argv, p->env);
				error("execve fucked up", p->cmd);
				ft_exit_son(sh, -1);
			}
			else if (p->pid < 0)
				error("fork fucked up", p->cmd);
		}
		else if (frk)
		{
			error("command not found", *p->argv);
			sh->process = sh->process->next;
			p->next = NULL;
			return (ft_free_tprocess(p));
		}
	}
	ft_get_envv_back(sh, p, t);
	return (p);
}
