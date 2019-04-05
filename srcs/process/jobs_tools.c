/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jobs_tools.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptruffau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/04 12:38:02 by ptruffau          #+#    #+#             */
/*   Updated: 2019/04/04 12:38:03 by ptruffau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell42.h"

int 	ft_get_new_id(t_jobs *j)
{
	t_jobs *head;
	int ret;

	ret = 1;
	head = j;
	while (j)
	{
		if (j->id == ret)
		{
			ret++;
			j = head;
		}
		else
			j = j->next;
	}
	return (ret);
}

static t_jobs	*ft_get_jobs_id(t_jobs *j, int id)
{
	int			i;

	i = 1;
	while (j)
	{
		if (j->id == id)
			return (j);
		j = j->next;
	}
	return (NULL);
}

static t_jobs	*ft_get_jobs_name(t_jobs *j, char *name)
{
	while (j)
	{
		if (ft_strstr(*j->p->argv, name) 
		|| ft_strstr(j->p->cmd, name))
			return (j);
		j = j->next;
	}
	return (NULL);
}

t_jobs	*ft_search_jobs(t_jobs *j, char *s)
{
	t_jobs *ret;

	if ((s && *s == '%' && ft_isdigit(s[1])
		&& (ret = ft_get_jobs_id(j, ft_atoi(&s[1]))))
		|| (s && (ret = ft_get_jobs_name(j, s))))
		return (ret);
	if (!s)
	{
		while (j && j->next)
			j = j->next;
		return (j);
	}
	return (NULL);
}


void	ft_remove_jobs(int pid, t_shell *sh)
{
	t_jobs *tmp;
	t_jobs *j;

	j = sh->jobs;
	if (j && j->p->pid == pid)
	{
		sh->jobs = j->next;
		j->next = NULL;
		ft_free_tjobs(j);
	}
	else if (j)
	{
		while (j->next)
		{
			if (j->next->p->pid == pid)
			{
				tmp = j->next;
				j->next = tmp->next;
				tmp->next = NULL;
				ft_free_tjobs(tmp);
				break ;
			}
			j = j->next;
		}
	}
}

void ft_add_jobs(t_process *p, t_shell *sh)
{
	t_jobs *n;
	t_jobs *tmp;
	int		id;

	n = NULL;
	id = 0;
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
}
