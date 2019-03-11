/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_process.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptruffau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/18 15:17:06 by ptruffau          #+#    #+#             */
/*   Updated: 2019/02/18 15:17:07 by ptruffau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/shell42.h"

static void			ft_init_fd(t_process *new)
{
	new->save[0] = 0;
	new->save[1] = 1;
	new->save[2] = 2;
	new->fd[0] = 0;
	new->fd[1] = 1;
	new->fd[2] = 2;
	new->pipe[0] = -1;
	new->pipe[1] = -1;
	new->status = INIT;
	new->ret = -1;
	new->argv = NULL;
	new->grp = NULL;
	new->next = NULL;
	new->pid = 0;
	new->env = NULL;
	new->builtins = FALSE;
}

static t_process	*ft_abort(t_process *p)
{
	t_process *tmp;

	while (p)
	{
		if (p->cmd && p->grp)
		{
			tmp = p->grp;
			p->grp = NULL;
			ft_close_pipe(p->pipe);
		}
		else if (!p->cmd)
			error("command not found", *p->argv);
		ft_free_tprocess(p);
		p = tmp;
	}
	return (NULL);
}

t_process			*init_process(t_tree *t, t_shell *sh)
{
	t_process	*new;

	new = NULL;
	if ((new = (t_process *)malloc(sizeof(t_process))))
	{
		ft_init_fd(new);
		ft_update_pwd(sh);
		if (!(new->argv = ft_twordto_arr(t->cmd)))
		{
			free(new);
			return (NULL);
		}
		if (check_builtin(*new->argv) && (new->cmd = ft_strdup(*new->argv)))
			new->builtins = TRUE;
		else
		{
			new->env = tenvv_to_tab(sh->env);
			new->cmd = get_bin_path(*new->argv, sh->env);
		}
	}
	return (new);
}

t_process *init_pipe_process(t_tree *t, t_shell *sh)
{
	t_process *head;
	t_process *tmp;

	if ((head = init_process(t, sh)) && head->cmd && !pipe(head->pipe))
	{
		tmp = head;
		while (t->o_type == O_PIPE)
		{	
			t = t->next;
			if ((tmp->grp = init_process(t, sh)) && tmp->grp->cmd)
			{
				tmp = tmp->grp;
				if (t->o_type == O_PIPE && t->next && pipe(tmp->pipe))
					ft_abort(head);
			}
			else
				ft_abort(head);
		}
	}
	else
		ft_abort(head);
	return (head);
}
