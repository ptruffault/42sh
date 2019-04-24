/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jobs_tools.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptruffau <ptruffau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/04 12:38:02 by ptruffau          #+#    #+#             */
/*   Updated: 2019/04/24 17:10:21 by fstadelw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "shell42.h"

static int		ft_get_new_id(t_jobs *j)
{
	t_jobs	*head;
	int		ret;

	ret = 1;
	head = j;
	while (j)
	{
		if (j->id == ret && j->p->status != RUNNING_FG)
		{
			ret++;
			j = head;
		}
		else
			j = j->next;
	}
	return (ret);
}

t_jobs			*ft_get_lastp_jobs(t_jobs *j)
{
	t_jobs *tmp;

	if ((tmp = ft_get_last_jobs(j, '+')))
	{
		while (j && j->next)
		{
			if (j->next->id == tmp->id)
				return (j);
			j = j->next;
		}
	}
	return (NULL);
}

int				ft_job_is_over(t_jobs *j)
{
	t_process *tmp;

	if (j && j->p)
	{
		tmp = j->p;
		while (tmp && tmp->cmd)
		{
			if (tmp && (tmp->status == RUNNING_FG
			|| tmp->status == RUNNING_BG
			|| tmp->status == SUSPENDED))
				return (0);
			tmp = tmp->grp;
		}
	}
	return (1);
}

t_jobs			*ft_remove_jobs(int pid, t_shell *sh)
{
	t_jobs *tmp;
	t_jobs *j;

	j = sh->jobs;
	if (j && j->p->pid == pid)
	{
		sh->jobs = j->next;
		j->next = NULL;
		j = ft_free_tjobs(j);
	}
	else if (j)
		while (j->next)
		{
			if (j->next->p->pid == pid)
			{
				tmp = j->next;
				j->next = tmp->next;
				tmp->next = NULL;
				tmp = ft_free_tjobs(tmp);
				break ;
			}
			j = j->next;
		}
	return (sh->jobs);
}

t_jobs			*ft_add_jobs(t_process *p, t_shell *sh)
{
	t_jobs	*n;
	t_jobs	*tmp;

	n = NULL;
	if (p && (n = (t_jobs *)malloc(sizeof(t_jobs))))
	{
		n->p = p;
		n->id = ft_get_new_id(sh->jobs);
		n->next = NULL;
		if (sh->jobs)
		{
			tmp = sh->jobs;
			while (tmp && tmp->next)
				tmp = tmp->next;
			tmp->next = n;
		}
		else
			sh->jobs = n;
	}
	return (n);
}
