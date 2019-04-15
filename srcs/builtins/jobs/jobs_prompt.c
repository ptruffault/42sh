/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jobs_prompt.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptruffau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/15 11:32:47 by ptruffau          #+#    #+#             */
/*   Updated: 2019/04/15 11:32:49 by ptruffau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell42.h"

static void	ft_print_cmd(char **cmd)
{
	int i;

	i = 0;
	ft_putstr("\x1B[1;39m");
	while (cmd[i])
		ft_printf(" %s\x1B[00m", cmd[i++]);
}

void		ft_job_prompt(t_jobs *j, int opts)
{
	char	*stat[6];

	ft_process_tab_status(stat);
	if (opts == 1)
		ft_putnbr(j->p->pid);
	else
	{
		ft_printf("\x1B[00;34m[\x1B[00m%i\x1B[00;34m]\x1B[00m ", j->id);
		if (!j->next || !j->next->p || j->next->p->status == RUNNING_FG)
			ft_printf(" + ");
		else if (j && j->next && (!j->next->next || !j->next->next->p
		|| j->next->next->p->status == RUNNING_FG))
			ft_printf(" - ");
		else
			ft_printf("   ");
		if (opts == 2)
			ft_printf(" %i ", j->p->pid);
		if (j->p->status != DONE && j->p->status != RUNNING_FG
			&& j->p->status != RUNNING_BG)
			ft_signal_check(j->p);
		else
			ft_printf(" %s \x1B[1;39m", stat[j->p->status]);
		ft_print_cmd(j->p->argv);
	}
	ft_putstr("\x1B[00m\n");
}
