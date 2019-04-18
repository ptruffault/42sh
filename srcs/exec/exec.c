/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptruffau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/05 13:26:09 by ptruffau          #+#    #+#             */
/*   Updated: 2019/03/26 17:21:55 by stdenis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell42.h"

static t_tree	*next_instruction(t_tree *t)
{
	unsigned int	tmp;

	if (t && t->o_type && t->next)
	{
		if (t->o_type == O_SEP || t->o_type == O_BACK)
			return (t->next);
		if (t->o_type == O_AND || t->o_type == O_OR)
		{
			if ((t->o_type == O_AND && t->ret == 0)
				|| (t->o_type == O_OR && t->ret != 0))
				return (t->next);
			else
			{
				tmp = t->o_type;
				while (t->next && (t->o_type == tmp || t->o_type == O_PIPE))
					t = t->next;
				return (t->next);
			}
		}
	}
	return (NULL);
}

static void		ft_post_exec(t_jobs *j, t_tree *t, t_process *p, t_shell *sh)
{
	if (p && j)
	{
		ft_link_process_to_term(p, sh);
		p->ret = ft_wait(j, sh, FALSE);
		t->ret = (p->valid ? p->ret : 127);
		if (p->background == FALSE && sh->interactive == TRUE && p)
			ft_tcsetpgrp(sh->std[0], sh->pgid);
		if (p->status != SUSPENDED && p->background == FALSE && !(sh->fc == TRUE))
		{
			p->status = INIT;
			sh->jobs = ft_remove_jobs(p->pid, sh);
		}
	}
	ft_reset_fd(sh);
}

static t_tree	*exec_instruction(t_tree *t, t_shell *sh)
{
	t_process	*p;
	t_jobs		*j;

	p = NULL;
	j = NULL;
	if (t->o_type == O_PIPE)
	{
		if (t->next && (p = init_pipe_process(t, sh)))
			j = exec_pipe(t, p, sh);
		while (t->o_type == O_PIPE && t->next)
			t = t->next;
	}
	else if ((p = init_process(t, sh)))
		j = ft_exec_process(p, sh, t);
	t->ret = (p ? p->ret : 1);
	ft_post_exec(j, t, p, sh);
	return (t);
}

t_tree			*exec_tree(t_tree *t, t_shell *sh)
{
	t_tree *tmp;

	tmp = t;
	while (tmp)
	{
		if (!tmp->cmd || !tmp->cmd->word)
		{
			if (t->assign)
			{
				sh->env = ft_push_tenvv(sh->env, t->assign, IN);
				tmp = next_instruction(tmp);
			}
			else if (tmp->o_type == O_SEP || tmp->o_type == 0
				|| tmp->o_type == O_BACK)
				tmp = tmp->next;
			else
				break ;
		}
		else if (((tmp = ft_expention(tmp))))
		{
			if ((tmp = exec_instruction(tmp, sh)))
				tmp = next_instruction(tmp);
		}
	}
	return (t);
}
