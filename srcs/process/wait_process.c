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

static void	ft_eval_status(t_process *p)
{
	if ((WIFSIGNALED(p->ret) || WIFSTOPPED(p->ret))
	&& p->builtins == FALSE)
	{
		p->status = (WIFSTOPPED(p->ret) || p->sig == SIGTSTP ? SUSPENDED : KILLED);
		p->sig = (WIFSTOPPED(p->ret) ? SIGTSTP : WTERMSIG(p->ret));
		if (ft_signal_check(p) && p->background == FALSE && p->status != SUSPENDED)
			ft_putchar_fd('\n', 2);
		p->ret = p->sig + 128;	
	}
	else if (WIFEXITED(p->ret))
	{
		p->ret = WEXITSTATUS(p->ret);
		p->status = DONE;
	}
}

int			ft_wait(t_jobs *j, t_shell *sh)
{
	int ret;
	t_process *p;

	ret = 0;
	p = (j ? j->p : NULL);
	while (p)
	{
		if ((p->pid == 0 && p->status != SUSPENDED && p->status != DONE 
			&& p->status != KILLED && 
			(p->status == RUNNING_FG
			|| p->status == RUNNING_BG))
			|| (p->status == RUNNING_FG
			&& waitpid(p->pid, &p->ret, WUNTRACED) > 0)
			|| (p->status == RUNNING_BG
			&& waitpid(p->pid, &p->ret, WUNTRACED | WNOHANG) > 0))
		{
			ft_eval_status(p);
			ret = p->ret;
			if (j && ft_job_is_over(j))
			{
				sh->jobs = ft_remove_jobs(p->pid, sh);
				break ;
			}
			else if (j && j->p->background == TRUE && p->pid == j->p->pid)
				ft_job_prompt(j, 0);
		}
		p = p->grp;
	}
	return (ret);
}

void		ft_wait_background(t_shell *sh)
{
	t_jobs *tmp;
	t_jobs *s;

	tmp = sh->jobs;
	while (tmp)
	{
		s = tmp->next;
		if (tmp->p->background == TRUE)
			ft_wait(tmp, sh);
		tmp = s;
	}
}
