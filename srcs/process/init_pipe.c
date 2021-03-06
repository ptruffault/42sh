/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptruffau <ptruffau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/08 16:20:02 by ptruffau          #+#    #+#             */
/*   Updated: 2019/04/24 17:10:56 by fstadelw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "shell42.h"

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
			tmp->grp->g_prev = tmp;
			tmp = tmp->grp;
			if (tmp->background == TRUE)
				ft_update_status(head, RUNNING_BG, 0);
			if (!tmp->cmd)
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
	if ((head = init_process(t, sh)))
	{
		if (!head->cmd)
			valid_pipe = 0;
		tmp = head;
		tmp = ft_init_pi(tmp, t, sh, &valid_pipe);
		head->next = sh->process;
		sh->process = head;
	}
	ft_get_envv_back(sh, head, t);
	if (!valid_pipe)
		ft_update_valid(head);
	return (head);
}
