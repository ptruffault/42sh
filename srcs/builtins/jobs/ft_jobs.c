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

static void	ft_job_prompt(t_jobs *j)
{
	char *stat[6];

	ft_process_tab_status(stat);
	ft_printf("[%i] %s %s\n", j->id, stat[j->p->status], j->p->line);
}

int			ft_jobs(t_shell *sh, char **argv)
{
	t_jobs		*tmp;

	(void)argv;
	tmp = sh->jobs;
	while (tmp)
	{
		ft_job_prompt(tmp);
		tmp = tmp->next;
	}
	return (0);
}
