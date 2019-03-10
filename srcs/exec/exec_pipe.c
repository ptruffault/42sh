/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptruffau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/08 13:53:23 by ptruffau          #+#    #+#             */
/*   Updated: 2019/02/18 13:51:14 by adi-rosa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/shell42.h"

static int		ft_close_pipe(int pipe[2])
{
	if (!ft_close(pipe[0])
	|| !ft_close(pipe[1]))
		return (0);
	return (1);
}

void	ft_wait_pipe(t_process *p)
{
	while (p)
	{
		if (p && p->pid > 0
		&& (waitpid(p->pid, &p->ret, WUNTRACED) >= 0))
		{
			ft_printf("~>%s done\n",p->cmd );
			if (p->status != KILLED && p->status != SUSPENDED)
					p->status = DONE;
			if (p->grp)
				ft_close_pipe(p->pipe);
		}
		p = p->grp;
	}
}

static void		ft_link_stdin(int pipe[2])
{
	dup2(pipe[0], STDIN_FILENO);
	ft_close(pipe[1]);
}

static void		ft_link_stdout(int pipe[2])
{
	dup2(pipe[1], STDOUT_FILENO);
	ft_close(pipe[0]);
}



t_tree			*exec_pipe(t_tree *t, t_process *p, t_shell *sh)
{
	t_process	*prev;
	t_process	*tmp;

	prev = NULL;
	tmp = p;
	while (tmp && tmp->cmd)
	{
		if ((tmp->pid = fork()) == 0)
		{
			if (prev)
				ft_link_stdin(prev->pipe);
			if (tmp->grp)
				ft_link_stdout(tmp->pipe);
			ft_exec_son(tmp, t, sh);
			exit(-1);
		}
		prev = tmp;
		tmp = tmp->grp;
		t = t->next;
	}
	ft_wait_pipe(p);
	return (t);
}

