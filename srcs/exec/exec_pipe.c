/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptruffau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/08 13:53:23 by ptruffau          #+#    #+#             */
/*   Updated: 2019/03/26 17:21:55 by stdenis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell42.h"

static t_process	*ft_stuff(t_process *prev, t_process *tmp, t_shell *sh)
{
	if (prev)
		ft_close_pipe(prev->pipe);
	else
		tmp->pgid = tmp->pid;
	if (sh->interactive == TRUE && setpgid(tmp->pid, tmp->pgid) < 0)
	{
		error("can't set group", tmp->cmd);
		tmp->ret = 1;
	}
	return (tmp);
}

static void			ft_son(t_process *p, t_process *tmp, t_shell *sh, t_tree *t)
{
	if ((p && !ft_link_stdin(p))
		|| (tmp->grp && !ft_link_stdout(tmp)))
		ft_exit_son(sh, -1, tmp);
	ft_exec_process(tmp, sh, t);
	ft_exit_son(sh, tmp->ret, tmp);
}

t_jobs				*exec_pipe(t_tree *t, t_process *p, t_shell *sh)
{
	t_process	*prev;
	t_process	*tmp;
	t_jobs		*ret;

	prev = NULL;
	tmp = p;
	ret = ft_add_jobs(p, sh);
	while (tmp)
	{
		if ((tmp->pid = fork()) == 0)
			ft_son(prev, tmp, sh, t);
		else if (tmp->pid < 0)
		{
			error("fork fucked up", tmp->cmd);
			p->ret = 1;
		}
		else
			prev = ft_stuff(prev, tmp, sh);
		t->ret = p->valid ? t->ret :127;
		if ((tmp = tmp->grp))
		{
			tmp->pgid = p->pgid;
			t = t->next;
		}
	}
	return (ret);
}
