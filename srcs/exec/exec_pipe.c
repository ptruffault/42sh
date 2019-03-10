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

void	ft_wait_pipe(t_process *p)
{
	while (p)
	{
		if (p && p->pid > 0)
		{
			waitpid(p->pid, &p->ret, WUNTRACED);
			if (p->status != KILLED && p->status != SUSPENDED)
				p->status = DONE;
			if (p->grp)
			{	
				ft_close(p->pipe[0]);
				ft_close(p->pipe[1]);
			}
		}
		p = p->grp;
	}
}

static int		ft_close_pipe(int pipe[2])
{
	if (!ft_close(pipe[0])
	|| !ft_close(pipe[1]))
		return (0);
	return (1);
}

static void		ft_link_stdin(int pipe[2])
{
	ft_printf("LINK STDIN");
	dup2(pipe[0], STDIN_FILENO);
	ft_close_pipe(pipe);
}

static void		ft_link_stdout(int pipe[2])
{
	ft_printf("LINK STDOUT");
	dup2(pipe[1], STDOUT_FILENO);
	ft_close_pipe(pipe);
}

static void		ft_link_both(int prev[2],int tmp[2])
{
	ft_printf("LINK BOTH");
	dup2(prev[0], STDIN_FILENO);
	dup2(tmp[1], STDOUT_FILENO);
	ft_close_pipe(prev);
	ft_close_pipe(tmp);
}

t_tree			*exec_pipe(t_tree *t, t_process *p, t_shell *sh)
{
	t_process	*prev;
	t_process	*tmp;

	prev = NULL;
	tmp = p;
	while (tmp && tmp->cmd)
	{
		printf("in loop {%s}\n", tmp->cmd);
		if ((tmp->pid = fork()) == 0)
		{
			if (prev && tmp->grp)
				ft_link_both(prev->pipe, tmp->pipe);
			else if (prev)
				ft_link_stdin(prev->pipe);
			else if (tmp->grp)
				ft_link_stdout(tmp->pipe);
			ft_exec_son(tmp, t, sh);
			exit(-1);
		}
		prev = tmp;
		tmp = tmp->grp;
		if (t->next)
			t = t->next;
	}
	ft_wait_pipe(p);
	return (t);
}

