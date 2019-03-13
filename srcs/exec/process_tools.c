/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptruffau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/08 14:07:56 by ptruffau          #+#    #+#             */
/*   Updated: 2019/02/18 14:00:30 by adi-rosa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/shell42.h"


static t_process	*ft_get_process(t_process *p)
{
	t_process *tmp;

	while (p)
	{
		if (p->status == RUNNING_FG && p->pid != 0)
			return (p);
		if (p->grp)
		{
			tmp = p->grp;
			while (tmp)
			{
				if (tmp->status == RUNNING_FG && p->pid != 0)
					return (tmp);
				tmp = tmp->grp;
			}
		}
		p = p->next;
	}
	return (NULL);
}

int			kill_running_fg_process(t_process *p, int sig)
{
	t_process *tmp;
	int i;

	i = 0;
	ft_putchar('\n');
	while (p && (tmp = ft_get_process(p)))
	{
		i++;
		if (sig == SIGINT)
			tmp->status = KILLED;
		else if (sig == SIGTSTP)
		{
			ft_printf("{%i} \033[00;31msuspended\033[00m %s\n", tmp->pid, tmp->cmd);
			tmp->status = SUSPENDED;
		}
		kill(tmp->pid, sig);
	}
	return (i);
}
