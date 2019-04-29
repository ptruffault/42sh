/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait_process.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptruffau <ptruffau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/04 12:36:33 by ptruffau          #+#    #+#             */
/*   Updated: 2019/04/24 17:10:08 by fstadelw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/wait.h>
#include "shell42.h"
#include "ft_printf.h"

static void	ft_eval_status(t_process *p, t_jobs *j)
{
	if ((WIFSIGNALED(p->ret) || WIFSTOPPED(p->ret))
		&& p->builtins == FALSE && p->cmd && p->valid)
	{
		p->status = (WIFSTOPPED(p->ret) ? SUSPENDED : KILLED);
		p->sig = (WIFSTOPPED(p->ret) ? SIGTSTP : WTERMSIG(p->ret));
		if (WIFSTOPPED(p->ret))
			ft_update_status(j->p, p->status, p->sig);
		if (ft_signal_check(p))
		{
			ft_putstr_fd(" : ", 2);
			ft_putendl_fd(p->cmd, 2);
		}
		p->ret = p->sig + 128;
	}
	else
	{
		if (WIFEXITED(p->ret))
			p->ret = WEXITSTATUS(p->ret);
		p->status = DONE;
	}
}

static int	ft_job_stuff(t_jobs *j, t_shell *sh)
{
	if (j && j->p->background == TRUE)
		ft_job_prompt(j, 0);
	if (sh->fc == FALSE && j && ft_job_is_over(j))
	{
		ft_update_status(j->p, DONE, 0);
		sh->jobs = ft_remove_jobs(j->p->pid, sh);
		return (0);
	}
	return (1);
}

int			ft_wait(t_process *p, t_jobs *j, t_shell *sh, t_bool fg)
{
	int			*ret;

	ret = &p->ret;
	while (p)
	{
		if ((((!p->cmd || p->pid == 0) && p->status != DONE
					&& p->status != KILLED)
				|| (fg && p->status == RUNNING_FG
					&& waitpid(p->pid, &p->ret, WUNTRACED) > 0)
				|| (!fg && (p->status == RUNNING_BG || p->status == SUSPENDED)
					&& waitpid(p->pid, &p->ret, WUNTRACED | WNOHANG) > 0)))
		{
			ft_eval_status(p, j);
			if (!ft_job_stuff(j, sh))
				break ;
		}
		p = p->grp;
	}
	return (*ret);
}

void		ft_wait_background(t_shell *sh)
{
	t_jobs *tmp;
	t_jobs *s;

	tmp = sh->jobs;
	while (tmp)
	{
		s = tmp->next;
		if (!ft_job_is_over(tmp))
			ft_wait(tmp->p, tmp, sh, FALSE);
		tmp = s;
	}
}
