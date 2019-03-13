/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fg_bg.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptruffau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/12 12:46:36 by ptruffau          #+#    #+#             */
/*   Updated: 2019/03/12 12:46:38 by ptruffau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/shell42.h"

t_process	*ft_get_process_id(t_process *p, int id)
{
	int i;

	i = 1;
	while (p)
	{
		if ((p->status == RUNNING_BG || p->status == SUSPENDED)
		&& p->builtins == FALSE && i++ == id)
			return (p);
		p = p->next;
	}
	return (NULL);
}

t_process *ft_get_process_name(t_process *p, char *name)
{
	while (p)
	{
		if ((p->status == RUNNING_BG || p->status == SUSPENDED) 
		&& (ft_strequ(p->cmd, name) || ft_strequ(*p->argv, name))
		&& p->pid > 0)
			return (p);
		p = p->next;
	}
	return (NULL);
}

void	ft_sigcont(t_process *tmp, unsigned int status)
{
	while (tmp)
	{
		if (tmp->status == SUSPENDED)
		{
			ft_printf("{%i}  \033[1;32mcontinued\033[00m %s\n", tmp->pid, tmp->cmd);
			tmp->status = status;
			kill(tmp->pid, SIGCONT);
		}
		tmp = tmp->grp;
	}
}

void 	ft_wait_fg(t_process *p)
{
	while (p)
	{
		waitpid(p->pid, &p->ret, WUNTRACED);
		if (p->status != SUSPENDED && p->status != KILLED)
			p->status = DONE;	
		p = p->grp;
	}
}

void ft_set_background(t_process *p)
{
	int pgid;

	ft_printf("{%i} running background %s\n", p->pid, p->cmd);
	pgid = getpgid(p->pid);
	p->status = RUNNING_BG;
	ft_sigcont(p, RUNNING_BG);
	tcsetpgrp(STDIN_FILENO, pgid);
	tcsetpgrp(STDOUT_FILENO, pgid);
	tcsetpgrp(STDERR_FILENO, pgid);
}


int ft_bg(t_shell *sh, char **argv)
{
	t_process *tmp;
	int i;

	i = 0;
	if ((!argv[1] && (tmp = ft_get_process_id(sh->process, 1))))
		ft_set_background(tmp);
	while (argv[++i])
	{
		if ((argv[1] && *argv[i] == '%' && ft_isdigit(argv[i][1])
		&& (tmp = ft_get_process_id(sh->process, ft_atoi(&argv[i][1]))))
		|| (argv[1] && (tmp = ft_get_process_name(sh->process, argv[i]))))
			ft_set_background(tmp);
		else
		{
			error("job not found", argv[1]);
			return (-1);
		}
	}
	return (0);
}

int ft_fg(t_shell *sh, char **argv)
{
	t_process *tmp;
	int i;

	i = 0;
	if ((!argv[1] && (tmp = ft_get_process_id(sh->process, 1))))
	{
		ft_sigcont(tmp, RUNNING_FG);
		ft_wait_fg(tmp);
	}
	while (argv[++i])
	{
		if ((argv[1] && *argv[i] == '%' && ft_isdigit(argv[i][1])
		&& (tmp = ft_get_process_id(sh->process, ft_atoi(&argv[i][1]))))
		|| (argv[1] && (tmp = ft_get_process_name(sh->process, argv[i]))))
		{
			ft_sigcont(tmp, RUNNING_FG);
			ft_wait_fg(tmp);
		}
		else
		{
			error("job not found", argv[1]);
			return (-1);
		}
	}
	return (0);
}