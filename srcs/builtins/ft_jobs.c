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

int		ft_jobs(t_shell *sh)
{
	t_process	*tmp;
	t_process	*grp;
	char		*stat[5];
	int			i;

	i = 0;
	stat[0] = "running foreground";
	stat[1] = "running background";
	stat[2] = "done";
	stat[3] = "suspended";
	stat[4] = "killed";
	tmp = sh->process;
	while (tmp)
	{
		if (tmp->cmd)
			ft_printf("[%i]\t%s -> %3i\t%s {%i}\n",
		i++, stat[tmp->status], tmp->ret, tmp->cmd, tmp->pid);
		if (tmp->grp)
		{
			grp = tmp->grp;
			while (grp)
			{
				if (grp->cmd)
					ft_printf("|->\t %s -> %3i\t%s {%i}\n",
					stat[grp->status], grp->ret, grp->cmd, grp->pid);
				grp = grp->grp;
			}
		}
		tmp = tmp->next;
	}
	return (0);
}
