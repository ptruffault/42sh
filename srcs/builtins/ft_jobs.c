/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_jobs.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptruffau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/08 12:42:19 by ptruffau          #+#    #+#             */
/*   Updated: 2019/03/20 18:11:13 by stdenis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <shell42.h>

static void ft_job_prompt(t_process *tmp, int id)
{
	t_process *grp;

	ft_printf("-\x1B[01;34m%- 2i\x1B[00m", id);
	ft_put_process(tmp);
	grp = tmp->grp;
	while (grp)
	{
		if (grp->cmd)
		{
			ft_printf("  \x1B[1;35m|\x1B[00m ");
			ft_put_process(grp);
		}
		grp = grp->grp;
	}
}

int		ft_hi(t_shell *sh)
{
	t_process	*tmp;
	int			id;

	id = 0;
	ft_printf("\x1B[04m ID  PID    RETURN   STATUS    PATH         \x1B[00m\n");
	tmp = sh->process;
	while (tmp)
	{
		if (tmp->cmd)
			ft_job_prompt(tmp, id++);
		tmp = tmp->next;
	}
	return (0);
}

int 	ft_jobs(t_shell *sh)
{
	t_process	*tmp;
	int			id;

	id = 0;
	tmp = sh->process;
	while (tmp)
	{
		if (tmp->status == RUNNING_BG || tmp->status == SUSPENDED)
			ft_job_prompt(tmp, id++);
		tmp = tmp->next;
	}
	return (0);
}
