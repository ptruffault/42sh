/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_kill.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptruffau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/08 16:54:17 by ptruffau          #+#    #+#             */
/*   Updated: 2019/04/08 16:54:18 by ptruffau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell42.h"

void	ft_update_status(t_process *p, unsigned int status)
{
	char *stat[6];

	ft_process_tab_status(stat);
	while (p)
	{
		ft_printf("%i %s %s\n", p->pid, stat[status], p->cmd);
		if (status == RUNNING_BG)
			p->background = TRUE;
		else if (status == RUNNING_FG)
			p->background = FALSE;
		p->status = status;
		p = p->grp;
	}
}

int		kill_process(t_process *p, int sig, unsigned int status)
{
	int i;

	i = 0;
	while (p)
	{
		if (p->status == status)
		{
			if (p->pid > 0 && p->status != DONE && p->status != KILLED)
			{
				p->sig = sig;
				if (kill(-p->pid, sig) < 0)
					warning("kill fucked up", p->cmd);
				i++;
			}
		}
		p = p->next;
	}
	return (i);
}
