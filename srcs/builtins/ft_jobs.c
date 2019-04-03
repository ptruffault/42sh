/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_jobs.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptruffau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/01 17:07:18 by ptruffau          #+#    #+#             */
/*   Updated: 2019/04/01 17:07:20 by ptruffau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell42.h"

static void	ft_job_prompt(t_process *p, int id)
{
	char *stat[6];

	ft_process_tab_status(stat);
	ft_printf("[%i] %s %s\n", id, stat[p->status], p->line);
}

int			ft_jobs(t_shell *sh, char **argv)
{
	t_process	*tmp;
	int			id;

	id = 0;
	(void)argv;
	tmp = sh->process;
	while (tmp)
	{
		if (tmp->builtins == FALSE && (tmp->status == RUNNING_BG
			|| tmp->status == SUSPENDED || tmp->status == RUNNING_FG))
			ft_job_prompt(tmp, id++);
		tmp = tmp->next;
	}
	return (0);
}
