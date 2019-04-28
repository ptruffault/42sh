/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_tools_shell.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptruffau <ptruffau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/08 15:26:10 by ptruffau          #+#    #+#             */
/*   Updated: 2019/04/24 16:46:23 by fstadelw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "shell42.h"

t_jobs	*ft_free_tjobs(t_jobs *j)
{
	t_jobs *tmp;

	while (j)
	{
		tmp = j->next;
		free(j);
		j = tmp;
	}
	return (NULL);
}

void	pre_free_process(t_process *p)
{
	while (p)
	{
		ft_freestrarr(&p->env);
		p->saved_env = ft_free_tenvv(p->saved_env);
		p = p->grp;
	}
}

void	ft_free_tshell(t_shell *sh)
{
	sh->env = ft_free_tenvv(sh->env);
	sh->alias = ft_free_tenvv(sh->alias);
	sh->process = ft_free_tprocess(sh->process);
	sh->hist = ft_free_thist(sh->hist);
	sh->jobs = ft_free_tjobs(sh->jobs);
	ft_strdel(&sh->clipboard);
	ft_strdel(&sh->txt);
}
