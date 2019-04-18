/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptruffau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/08 16:20:02 by ptruffau          #+#    #+#             */
/*   Updated: 2019/04/08 16:20:03 by ptruffau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell42.h"

static t_process	*ft_abort(t_process *p, const char *err, t_process *tmp)
{
	t_process *head;

	head = p;
	error(err, *tmp->argv);
	while (p && p->cmd)
	{
		if (p->grp)
			ft_close_pipe(p->pipe);
		p = p->grp;
	}
	return (ft_free_tprocess(head));
}

static void			ft_update_valid(t_process *p)
{
	while (p)
	{
		p->valid = 0;
		p->ret = 127;
		p = p->grp;
	}
}

static t_process	*ft_init_pi(t_process *tmp, t_tree *t, t_shell *sh, int *v)
{
	t_process *head;

	head = tmp;
	while (t && t->o_type == O_PIPE)
	{
		t = t->next;
		if (t && (tmp->grp = init_process(t, sh)))
		{
			tmp = tmp->grp;
			if (tmp->background == TRUE)
				ft_update_status(head, RUNNING_BG);
			if (tmp->cmd)
			{
				if (t->o_type == O_PIPE && t->next
					&& (pipe(tmp->pipe) < 0))
					return (ft_abort(head, "broken pipe", tmp));
			}
			else
				*v = 0;
			ft_get_envv_back(sh, tmp, t);
		}
	}
	return (tmp);
}

t_process			*init_pipe_process(t_tree *t, t_shell *sh)
{
	t_process	*head;
	t_process	*tmp;
	int			valid_pipe;

	head = NULL;
	tmp = NULL;
	valid_pipe = 1;
	if ((head = init_process(t, sh)) && !pipe(head->pipe))
	{
		if (!head->cmd)
			valid_pipe = 0;
		tmp = head;
		if (!(tmp = ft_init_pi(tmp, t, sh, &valid_pipe)))
			return (NULL);
		head->next = sh->process;
		sh->process = head;
	}
	ft_get_envv_back(sh, head, t);
	if (!valid_pipe)
		ft_update_valid(head);
	return (head);
}
