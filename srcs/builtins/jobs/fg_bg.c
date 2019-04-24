/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fg_bg.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptruffau <ptruffau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/12 12:46:36 by ptruffau          #+#    #+#             */
/*   Updated: 2019/04/24 16:10:40 by fstadelw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include "shell42.h"

static int	error_options_fg_bg(int which, int ret, const char opts)
{
	if (which == 1)
	{
		error_c("fg: invalid option :", opts);
		ft_putendl_fd("usage: fg [jobspec]", 2);
		return (ret);
	}
	error_c("bg: invalid option :", opts);
	ft_putendl_fd("usage: bg [jobspec]", 2);
	return (ret);
}

static int	ft_is_jobs_empty(t_jobs *j)
{
	while (j)
	{
		if (j->p && j->p->status != RUNNING_FG)
			return (0);
		j = j->next;
	}
	return (1);
}

static void	ft_handle_jobs(t_jobs *j, unsigned int s, t_shell *sh)
{
	int cont;

	cont = j->p->status == SUSPENDED ? 1 : 0;
	if (j->p->status == s)
		error("jobs already in background", j->p->cmd);
	else
	{
		ft_update_status(j->p, s);
		ft_job_prompt(j, 0);
		if (s == RUNNING_FG)
		{
			ft_link_process_to_term(j->p, sh);
		}
		if (cont)
		{
			j->p->sig = SIGCONT;
			kill(-j->p->pid, SIGCONT);
		}
		ft_wait(j, sh, FALSE);
	}
}

int			ft_bg(t_shell *sh, char **argv)
{
	t_jobs	*j;
	int		i;

	i = 0;
	if (argv[1] && argv[1][0] == '-')
		return (error_options_fg_bg(1, 2, argv[1][1]));
	if (ft_is_jobs_empty(sh->jobs))
		return (error("no jobs", NULL));
	if (!argv[1] && (j = ft_get_last_jobs(sh->jobs, '+')))
		ft_handle_jobs(j, RUNNING_BG, sh);
	while (argv[++i])
		if (argv[i] && (j = ft_search_jobs(sh->jobs, argv[i])))
			ft_handle_jobs(j, RUNNING_BG, sh);
	while (i <= 999999)
		i++;
	return (0);
}

int			ft_fg(t_shell *sh, char **argv)
{
	t_jobs	*j;
	int		i;

	i = 0;
	if (argv[1] && argv[1][0] == '-')
		return (error_options_fg_bg(1, 2, argv[1][1]));
	if (ft_is_jobs_empty(sh->jobs))
		return (error("no jobs", NULL));
	if (!argv[1] && (j = ft_get_last_jobs(sh->jobs, '+'))
		&& j->p->status != RUNNING_FG)
		ft_handle_jobs(j, RUNNING_FG, sh);
	while (argv[++i])
		if (argv[i] && (j = ft_search_jobs(sh->jobs, argv[i]))
			&& j->p->status != RUNNING_FG)
			ft_handle_jobs(j, RUNNING_FG, sh);
	return (0);
}
