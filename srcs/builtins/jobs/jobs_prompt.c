/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jobs_prompt.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptruffau <ptruffau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/15 11:32:47 by ptruffau          #+#    #+#             */
/*   Updated: 2019/04/24 16:30:10 by fstadelw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "shell42.h"

static int	ft_test_over(t_process *p)
{
	unsigned int s;

	s = p->status;
	while (p)
	{
		if (p->status != s)
			return (0);
		p = p->grp;
	}
	return (1);
}

static void	ft_print_cmd(t_process *p)
{
	int i;

	while (p)
	{
		i = 0;
		while (p->argv[i])
			ft_printf(" %s ", p->argv[i++]);
		if ((p = p->grp))
			ft_putchar('|');
	}
}

void		ft_prompt(t_process *p, int opts)
{
	char	*stat[6];

	ft_process_tab_status(stat);
	if (opts == 2)
		ft_printf(" %i ", p->pid);
	if (p->status != DONE && p->status != RUNNING_FG
		&& p->status != RUNNING_BG)
		ft_signal_check(p);
	else
		ft_printf(" %s \x1B[1;39m", stat[p->status]);
}

void		ft_prompt_cmd(t_process *p, int opts)
{
	int i;

	if (!ft_test_over(p))
	{
		while (p)
		{
			i = 0;
			ft_prompt(p, opts);
			while (p->argv[i])
				ft_printf(" %s ", p->argv[i++]);
			ft_putstr("\x1B[00m\n");
			if ((p = p->grp))
				ft_putstr("       ");
		}
	}
	else
	{
		ft_prompt(p, opts);
		ft_print_cmd(p);
		ft_putstr("\x1B[00m\n");
	}
}

void		ft_job_prompt(t_jobs *j, int opts)
{
	if (opts == 1)
		ft_printf("%d\n", j->p->pid);
	else
	{
		ft_printf("\x1B[00;34m[\x1B[00m%i\x1B[00;34m]\x1B[00m ", j->id);
		if (!j->next || !j->next->p || j->next->p->status == RUNNING_FG)
			ft_printf(" + ");
		else if (j && j->next && (!j->next->next || !j->next->next->p
		|| j->next->next->p->status == RUNNING_FG))
			ft_printf(" - ");
		else
			ft_printf("   ");
		ft_prompt_cmd(j->p, opts);
	}
}
