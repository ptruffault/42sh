/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_jobs.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptruffau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/01 17:07:18 by ptruffau          #+#    #+#             */
/*   Updated: 2019/04/01 17:07:20 by ptruffau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell42.h"

static void	ft_print_coresspond_jobs(t_jobs *j, char *str, int opts)
{
	t_jobs	*tmp;
	t_jobs	*jobs;
	int		err;

	err = 0;
	tmp = j;
	jobs = NULL;
	if (*str == '-')
		if ((jobs = ft_search_jobs(tmp, "")))
		{
			ft_job_prompt(jobs, opts);
			err++;
		}
	while ((jobs = ft_search_jobs(tmp, str)) && *str != '-')
	{
		err++;
		ft_job_prompt(jobs, opts);
		tmp = jobs->next;
		jobs = NULL;
	}
	if (!err)
		error("no such jobs", str);
}

static int	ft_init_opts(int ret, char *str)
{
	int i;

	i = 0;
	while (str[++i])
	{
		if (str[i] == 'l')
			ret = 2;
		else if (str[i] == 'p')
			ret = 1;
		else
			warning_c("unknow option", str[i]);
	}
	return (ret);
}

static int	ft_read_opts(char **argv, t_shell *sh)
{
	bool	check_opts;
	int		i;
	int		ret;
	int		n;

	i = 0;
	n = 0;
	ret = 0;
	check_opts = true;
	while (argv[++i])
	{
		if (check_opts && *argv[i] == '-' && argv[i][1] != '-')
			ret = ft_init_opts(ret, argv[i]);
		else if (check_opts && *argv[i] == '-' && argv[i][1] == '-')
			check_opts = false;
		else if (argv[i])
		{
			n = 3;
			ft_print_coresspond_jobs(sh->jobs, argv[i], ret);
		}
	}
	return ((!n ? ret : n));
}

int			ft_jobs(t_shell *sh, char **argv)
{
	t_jobs		*tmp;
	int			aff;

	tmp = sh->jobs;
	aff = ft_read_opts(argv, sh);
	if (aff < 3)
	{
		while (tmp)
		{
			if (tmp->p->status != RUNNING_FG)
				ft_job_prompt(tmp, aff);
			tmp = tmp->next;
		}
	}
	return (0);
}
