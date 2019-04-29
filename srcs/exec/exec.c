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
#include "ft_printf.h"

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

static int		ft_get_last_job_return(t_process *p)
{
	while (p && p->grp)
	{
		if (p->ret == 127 || p->ret == 126)
			return (p->ret);
		p = p->grp;
	}
	if (p)
		return (p->ret);
	return (0);
}

static void		ft_post_exec(t_jobs *j, t_tree *t, t_process *p, t_shell *sh)
{
	if (p && j)
	{
		t->ret = ft_wait(p, j, sh, TRUE);
		pre_free_process(p);
		if (p->background == FALSE)
		{
			t->ret = ft_get_last_job_return(p);
			sh->env = ft_new_envv_int(sh->env, "?", t->ret, IN);
		}
		if (p->background == FALSE && sh->interactive == TRUE && p)
			ft_tcsetpgrp(sh->std[0], sh->pgid);
		if (p->status != SUSPENDED && p->background == FALSE
			&& !(sh->fc == TRUE))
			sh->jobs = ft_remove_jobs(p->pid, sh);
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
	if (p->status == RUNNING_FG)
		ft_tcsetpgrp(sh->std[0], p->pgid);
	t->ret = (p ? p->ret : 1);
	if (t->ret != -1)
		sh->env = ft_new_envv_int(sh->env, "?", t->ret, IN);
	ft_post_exec(j, t, p, sh);
	return (t);
}

t_tree			*exec_tree(t_tree *t, t_shell *sh)
{
	t_tree *tmp;

	tmp = t;
	while (tmp)
		if (!tmp->cmd || !tmp->cmd->word)
		{
			if (tmp->r && ft_redirect_builtin(tmp, NULL, sh))
				ft_reset_fd(sh);
			if (tmp->ass)
			{
				sh->env = ft_push_tenvv(sh->env, tmp->ass, IN);
				tmp = next_instruction(tmp);
			}
			else if (tmp->o_type == O_SEP || tmp->o_type == 0
				|| tmp->o_type == O_BACK)
				tmp = tmp->next;
			else
				break ;
		}
		else if ((tmp = ft_expention(tmp)) && sh->exp_leave == 1)
			return (t);
		else if (tmp && (tmp = exec_instruction(tmp, sh)))
			tmp = next_instruction(tmp);
	return (t);
}
