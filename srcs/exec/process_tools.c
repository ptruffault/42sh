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

t_process	*ft_get_process(t_process *p, int stat)
{
	t_process *tmp;

	while (p)
	{
		if (p->grp)
		{
			tmp = p->grp;
			while (tmp)
			{
				if (tmp->status == stat)
					return (tmp);
				tmp = tmp->grp;
			}
		}
		if (p->status == stat)
			return (p);
		p = p->next;
	}
	return (NULL);
}

int			kill_running_fg_process(t_process *p, int sig)
{
	t_process *tmp;
	int i;

	i = 0;
	while (p && (tmp = ft_get_process(p, RUNNING_FG)))
	{
		i++;
		if (sig == SIGINT)
			tmp->status = KILLED;
		else if (sig == SIGTSTP)
			tmp->status = SUSPENDED;
		kill(tmp->pid, sig);
	}
	return (i);
}
