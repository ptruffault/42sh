/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fg_bg.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptruffau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/12 12:46:36 by ptruffau          #+#    #+#             */
/*   Updated: 2019/03/26 17:21:55 by stdenis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell42.h"

void		ft_handle_jobs(t_process *p, unsigned int s, t_shell *sh)
{
	if (p->status == SUSPENDED)
	{
		p->sig = SIGCONT;
		kill(-p->pid, SIGCONT);
	}
	if (p->status == s)
		error("jobs already in background", p->cmd);
	else
	{
		ft_update_status(p, s);
		if (s == RUNNING_FG)
			ft_link_process_to_term(p, sh);
		ft_wait(p, sh);
	}
}

int			ft_bg(t_shell *sh, char **argv)
{
	t_jobs	*j;
	int		i;

	i = 0;
	if (!sh->jobs)
		return (error("no jobs", NULL));
	if (!argv[1] && (j = ft_search_jobs(sh->jobs, NULL)))
		ft_handle_jobs(j->p, RUNNING_BG, sh);
	while (argv[++i])
		if (argv[i] && (j = ft_search_jobs(sh->jobs, argv[i])))
			ft_handle_jobs(j->p, RUNNING_BG, sh);
	while (i <= 999999)
		i++;
	return (0);
}

int			ft_fg(t_shell *sh, char **argv)
{
	t_jobs	*j;
	int		i;

	i = 0;
	if (!sh->jobs)
		return (error("no jobs", NULL));
	if (!argv[1] && (j = ft_search_jobs(sh->jobs, NULL)))
		ft_handle_jobs(j->p, RUNNING_FG, sh);
	while (argv[++i])
		if (argv[i] && (j = ft_search_jobs(sh->jobs, argv[i])))
			ft_handle_jobs(j->p, RUNNING_FG, sh);
	return (0);
}
