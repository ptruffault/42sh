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

static t_process	*ft_abort(t_process *p, char *err, t_process *tmp)
{
	t_process *head;

	head = p;
	error(err, *tmp->argv);
	while (p && p->cmd)
	{
		if (p->grp)
		{
			ft_close(p->pipe[0]);
			ft_close(p->pipe[1]);
		}
		p = p->grp;
	}
	return (ft_free_tprocess(head));
}

static void			ft_update_bg(t_process *p, t_bool val)
{
	while (p)
	{
		p->background = val;
		p = p->grp;
	}
}

static t_process	*ft_init_pi(t_process *tmp, t_tree *t, t_shell *sh)
{
	t_process *head;

	head = tmp;
	while (t->o_type == O_PIPE)
	{
		t = t->next;
		if (t && (tmp->grp = init_process(t, sh)))
		{
			tmp = tmp->grp;
			if (tmp->background == TRUE)
				ft_update_bg(head, TRUE);
			if (tmp->cmd)
			{
				if (t->o_type == O_PIPE && t->next
					&& (pipe(tmp->pipe) < 0))
					return (ft_abort(head, "broken pipe", tmp));
			}
			else
				return (ft_abort(head, "command not found", tmp));
		}
	}
	return (tmp);
}

t_process			*init_pipe_process(t_tree *t, t_shell *sh)
{
	t_process *head;
	t_process *tmp;

	head = NULL;
	tmp = NULL;
	if ((head = init_process(t, sh)) && !pipe(head->pipe))
	{
		if (!head->cmd)
			return (ft_abort(head, "command not found", head));
		tmp = head;
		if (!(tmp = ft_init_pi(tmp, t, sh)))
			return (NULL);
		head->next = sh->process;
		sh->process = head;
	}
	return (head);
}
