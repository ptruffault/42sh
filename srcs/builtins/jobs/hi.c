/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_jobs.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptruffau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/08 12:42:19 by ptruffau          #+#    #+#             */
/*   Updated: 2019/03/26 17:21:55 by stdenis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell42.h"

static void		ft_putpid_ret(t_process *p)
{
	t_shell *sh;

	if (p->pid > 0)
		ft_printf("\x1B[00;34m{\x1B[00m%i\x1B[00;34m}\x1B[00m ", p->pid);
	else if ((sh = ft_get_set_shell(NULL)))
		ft_printf("\x1B[00;34m{\x1B[01;36m%i\x1B[00m\x1B[00;34m}\x1B[00m "
		, sh->pid);
	if (p->status == DONE || p->status == SUSPENDED || p->status == KILLED)
	{
		if (p->ret == 0)
			ft_printf("\x1b[1;32;42m  0  \x1B[00m ", p->ret);
		else
			ft_printf("\x1b[1;34;41m%-4i \x1B[00m ", p->ret);
	}
	else
		ft_printf("      ");
}

static void		ft_hi_prompt(t_process *tmp, int id)
{
	t_process *grp;

	if (id != -1)
		ft_printf("-\x1B[01;34m%- 2i\x1B[00m", id);
	else
		ft_putstr("    ");
	ft_put_process(tmp);
	grp = tmp->grp;
	while (grp)
	{
		if (grp->cmd)
		{
			ft_printf(" \x1B[1;35m|\x1B[00m ");
			ft_put_process(grp);
		}
		grp = grp->grp;
	}
}

void			ft_process_tab_status(char *stat[6])
{
	stat[0] = "\x1b[1;34;41minitialised\x1B[00m";
	stat[1] = "\x1b[1;34;44mrunning fg \x1B[00m";
	stat[2] = "\x1b[1;34;44mrunning bg \x1B[00m";
	stat[3] = "\x1b[1;32;42m   done    \x1B[00m";
	stat[4] = "\x1b[1;36;46m suspended \x1B[00m";
	stat[5] = "\x1b[1;34;41m  killed   \x1B[00m";
}

void			ft_put_process(t_process *p)
{
	char *stat[6];

	ft_process_tab_status(stat);
	ft_putpid_ret(p);
	ft_printf("%-25s", stat[p->status]);
	if (p->builtins == TRUE)
		ft_printf(" \x1B[1;36m%-17s\x1B[00;31m", p->cmd);
	else
		ft_printf(" %-17s\x1B[00;31m", p->cmd);
	ft_signal_check(p);
	ft_putstr("\x1B[00m\n");
}

int				ft_hi(t_shell *sh)
{
	t_process	*tmp;
	int			id;

	id = 0;
	if (!isatty(0))
	{
		ft_hi_prompt(sh->process, -1);
		return (0);
	}
	ft_printf("\x1B[04m ID  PID    RETURN   STATUS    PATH         \x1B[00m\n");
	tmp = sh->process;
	while (tmp)
	{
		ft_hi_prompt(tmp, id++);
		tmp = tmp->next;
	}
	return (0);
}
