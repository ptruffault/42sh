/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptruffau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/08 14:02:44 by ptruffau          #+#    #+#             */
/*   Updated: 2019/02/18 13:52:08 by adi-rosa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <shell42.h>

static void	ft_son(t_tree *t, t_process *p, t_shell *sh)
{
	execve(p->cmd, p->argv, p->env);
	warning("execve fucked up", p->cmd);
	ft_reset_fd(p);
	ft_free_tshell(sh);
	ft_free_tree(t);
	exit(-1);
}

int			ft_execve(t_process *p, t_shell *sh, t_tree *t)
{
	if (!t->r || (t->r && ft_redirect_builtin(t, p)))
	{
		if (p->cmd && !ft_isempty(p->cmd))
		{
			p->status = RUNNING_FG;
			if (p->builtins == TRUE)
			{
				t->ret = run_builtin(t, p->argv, sh);
				p->ret = t->ret;
				ft_reset_fd(p);
				return (p->ret);
			}
			else if ((p->pid = fork()) == 0)
				ft_son(t, p, sh);
			if (t->o_type == O_BACK)
				ft_set_background(p, 0);
			return (-2);
		}
		else
			error("command not found", *p->argv);
	}
	ft_reset_fd(p);
	return (-1);
}
