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
		{
			kill(-tmp->pid, SIGCONT);
			tmp->background = TRUE;
			ft_update_status(tmp, RUNNING_BG);
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
			ft_update_status(tmp, RUNNING_BG);
			tmp->background = TRUE;
			kill(-tmp->pid, SIGCONT);
		}
		else
			return (error("job not found", argv[1]) - 1);
	}
	while (i < 1000000)
		i++;
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
			kill(-tmp->pid, SIGCONT);
			tmp->background = FALSE;
			ft_update_status(tmp, RUNNING_FG);
			ft_wait(tmp, sh);
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
			kill(-tmp->pid, SIGCONT);
			tmp->background = FALSE;
			ft_update_status(tmp, RUNNING_FG);
			ft_wait(tmp, sh);
		}
		else
			ret = error("job not found", argv[i]) - 1;
	}
	return (ret);
}
