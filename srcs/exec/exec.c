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
	unsigned int tmp;

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

t_tree			*exec_instruction(t_tree *t, t_shell *sh)
{
	t_process	*p;

	p = NULL;
	if (t->o_type == O_PIPE)
	{
		if (t->next && (p = init_pipe_process(t, sh)))
		{
			p->next = sh->process;
			sh->process = p;
			t = exec_pipe(t, p, sh);
		}
		else
			while (t->o_type == O_PIPE)
				t = t->next;
	}
	else if ((p = init_process(t, sh)))
	{
		p->next = sh->process;
		sh->process = p;
		p = ft_execve(p, sh, t, 1);
	}
	t->ret = (p ? ft_wait(p) : -1);
	ft_reset_fd(sh);
	if (p && p->background == TRUE)
	{
		ft_printf("jes uis la\n");
		ft_killgrp(p, -1);
	}
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
				sh->intern = ft_push_tenvv(sh->intern, t->assign);
			if (tmp->o_type == O_SEP || tmp->o_type == 0
				|| tmp->o_type == O_BACK)
				tmp = tmp->next;
			else
				break ;
		}
		else if (!(tmp = exec_instruction(tmp, sh)))
			break ;
		tmp = next_instruction(tmp);
	}
	return (t);
}
