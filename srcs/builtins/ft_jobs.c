/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_jobs.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptruffau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/08 12:42:19 by ptruffau          #+#    #+#             */
/*   Updated: 2019/02/19 13:10:50 by adi-rosa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/shell42.h"

static void ft_init_status(char *stat[6])
{
	stat[0] = "initialised";
	stat[1] = "running foreground";
	stat[2] = "running background";
	stat[3] = "done";
	stat[4] = "suspended";
	stat[5] = "killed";
}

static void ft_job_prompt(t_process *tmp, char *stat[6], int id)
{
	ft_printf("[%i] %s\t%3i %s {%i}\n",
	id, stat[tmp->status], tmp->ret, tmp->cmd, tmp->pid);
}



int		ft_jobs(t_shell *sh)
{
	t_process	*tmp;
	t_process	*grp;
	char 		*stat[6];
	int			id;

	id = 0;
	tmp = sh->process;
	ft_init_status(stat);
	while (tmp)
	{
		if (tmp->cmd)
			ft_job_prompt(tmp, stat, id++);
		if (tmp->grp)
		{
			grp = tmp->grp;
			while (grp)
			{
				if (grp->cmd)
					ft_printf(" |  %s\t%3i %s {%i}\n",
					stat[grp->status], grp->ret, grp->cmd, grp->pid);
				grp = grp->grp;
			}
		}
		tmp = tmp->next;
	}
	return (0);
}
