/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fg_bg.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptruffau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/12 12:46:36 by ptruffau          #+#    #+#             */
/*   Updated: 2019/03/20 18:11:13 by stdenis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <shell42.h>

static t_process	*ft_get_process_id(t_process *p, int id)
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

static t_process 	*ft_get_process_name(t_process *p, char *name)
{
	while (p)
	{
		if ((p->status == RUNNING_BG || p->status == SUSPENDED) 
			&& p->builtins == FALSE && (ft_strequ(p->cmd, name) 
			|| ft_strequ(*p->argv, name)))
			return (p);
		p = p->next;
	}
	return (NULL);
}

int ft_bg(t_shell *sh, char **argv)
{
	t_process *tmp;
	int i;

	i = 0;
	if (!argv[1])
	{
		if ((tmp = ft_get_process_id(sh->process, 1)))
			ft_killgrp(tmp, -1);
		else
			return (error("no current job", NULL) - 1);
	}
	while (argv[++i])
	{
		if ((argv[1] && *argv[i] == '%' && ft_isdigit(argv[i][1])
			&& (tmp = ft_get_process_id(sh->process, ft_atoi(&argv[i][1]))))
			|| (argv[1] && (tmp = ft_get_process_name(sh->process, argv[i]))))
			ft_killgrp(tmp, -1);
		else
			return (error("job not found", argv[1]) - 1);
	}
	return (0);
}

int ft_fg(t_shell *sh, char **argv)
{
	t_process *tmp;
	int i;
	int ret;

	i = 0;
	ret = 0;
	if (!argv[1])
	{
		if ((tmp = ft_get_process_id(sh->process, 1)))
		{
			ft_killgrp(tmp, SIGCONT);
			ft_wait(tmp);
		}
		else
			return (error("no current job", NULL) - 1);
	}
	while (argv[++i])
	{
		if ((argv[1] && *argv[i] == '%' && ft_isdigit(argv[i][1])
			&& (tmp = ft_get_process_id(sh->process, ft_atoi(&argv[i][1]))))
			|| (argv[1] && (tmp = ft_get_process_name(sh->process, argv[i]))))
		{
			ft_killgrp(tmp, SIGCONT);
			ft_wait(tmp);
		}
		else
			ret = error("job not found", argv[i]) - 1;
	}
	return (ret);
}
