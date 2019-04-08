/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait_process.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptruffau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/04 12:36:33 by ptruffau          #+#    #+#             */
/*   Updated: 2019/04/04 12:36:35 by ptruffau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell42.h"

static void	ft_eval_status(t_process *p, t_shell *sh)
{
	if (WIFCONTINUED(p->ret) && p->status == RUNNING_FG
		&& p->builtins == FALSE)
		ft_wait(p, sh);
	else if (WIFSTOPPED(p->ret) && p->builtins == FALSE)
		p->status = SUSPENDED;
	else if (WIFSIGNALED(p->ret) && p->builtins == FALSE)
	{
		p->status = KILLED;
		p->sig = WTERMSIG(p->ret);
		p->ret = p->sig + 128;
	}
	else if (WIFEXITED(p->ret))
	{
		p->ret = WEXITSTATUS(p->ret);
		p->status = DONE;
	}
	else if (p->status == RUNNING_BG || p->status == RUNNING_FG)
		p->status = DONE;
}

int			ft_wait(t_process *p, t_shell *sh)
{
	int ret;

	ret = 0;
	while (p)
	{
		if ((p->builtins == TRUE && (p->status == RUNNING_FG
			|| p->status == RUNNING_BG))
			|| (p->status == RUNNING_FG
			&& waitpid(p->pid, &p->ret, WUNTRACED) > 0)
			|| (p->status == RUNNING_BG
			&& waitpid(p->pid, &p->ret, WUNTRACED | WNOHANG) > 0))
		{
			ft_eval_status(p, sh);
			if (p->status != DONE || p->background == TRUE)
				ft_put_process(p);
			if (p->status == DONE || p->status == KILLED)
				ft_remove_jobs(p->pid, sh);
			sh->env = ft_new_envv_int(sh->env, "?", p->ret, false);
			ret = ret + p->ret;
		}
		p = p->grp;
	}
	return (ret);
}

void		ft_wait_background(t_shell *sh)
{
	t_process *tmp;

	tmp = sh->process;
	while (tmp)
	{
		if (tmp->status == RUNNING_BG)
			ft_wait(tmp, sh);
		tmp = tmp->next;
	}
}
