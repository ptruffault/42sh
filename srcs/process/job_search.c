/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job_search.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptruffau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/08 16:56:02 by ptruffau          #+#    #+#             */
/*   Updated: 2019/04/08 16:56:03 by ptruffau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell42.h"

static t_jobs	*ft_get_jobs_id(t_jobs *j, int id)
{
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

t_jobs	*ft_get_jobs_pid(t_jobs *j, int pid)
{
	while (j)
	{
		if (j->p->pid == pid)
			return (j);
		j = j->next;
	}
	return (NULL);
}

t_jobs			*ft_search_jobs(t_jobs *j, char *s)
{
	t_jobs *ret;

	ret = NULL;
	if (s && ((*s == '%' && ft_isdigit(s[1])
		&& (ret = ft_get_jobs_id(j, ft_atoi(&s[1]))))
		|| (ft_isdigit(s[0]) && ft_get_jobs_pid(j, ft_atoi(s)))
		|| (ret = ft_get_jobs_name(j, s))))
		return (ret);
	if (!s)
	{
		while (j && j->next)
			j = j->next;
		return (j);
	}
	return (NULL);
}
