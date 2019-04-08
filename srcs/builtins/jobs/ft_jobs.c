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

static void	ft_job_prompt(t_jobs *j, int opts)
{
	char	*stat[6];
	int		i;

	i = 0;
	ft_process_tab_status(stat);
	if (opts == 1)
		ft_putnbr(j->p->pid);
	else
	{
		ft_printf("[%i] ", j->id);
		if (!j->next)
			ft_printf(" + ");
		else if (j && j->next && !j->next->next)
			ft_printf(" - ");
		else
			ft_printf("   ");
		if (opts == 2)
			ft_printf(" %i ", j->p->pid);
		ft_printf("%s ", stat[j->p->status]);
		while (j->p->argv[i])
			ft_printf("%s ", j->p->argv[i++]);
	}
	ft_putchar('\n');
}

static void	ft_print_coresspond_jobs(t_jobs *j, char *str, int opts)
{
	t_jobs	*tmp;
	t_jobs	*jobs;
	int		err;

	err = 0;
	tmp = j;
	jobs = NULL;
	while ((jobs = ft_search_jobs(tmp, str)))
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
			ret = (!ret ? 1 : ret);
		else
			warning_c("unknow option", str[i]);
	}
	return (ret);
}

static int	ft_read_opts(char **argv, t_shell *sh)
{
	int i;
	int ret;
	int n;

	i = 0;
	n = 0;
	ret = 0;
	while (argv[++i])
	{
		if (*argv[i] == '-')
			ret = ft_init_opts(ret, argv[i]);
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
			ft_job_prompt(tmp, aff);
			tmp = tmp->next;
		}
	}
	return (0);
}
