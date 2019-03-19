/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_process.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptruffau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/18 15:17:06 by ptruffau          #+#    #+#             */
/*   Updated: 2019/03/19 15:41:07 by stdenis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <shell42.h>

static void			ft_init_fd(t_process *new, t_shell *sh)
{
	new->fd[0] = sh->std[0];
	new->fd[1] = sh->std[1];
	new->fd[2] = sh->std[2];
	new->pgid = 0;
	new->pipe[0] = -1;
	new->pipe[1] = -1;
	new->status = INIT;
	new->ret = -1;
	new->argv = NULL;
	new->grp = NULL;
	new->next = NULL;
	new->pid = -1;
	new->env = NULL;
	new->builtins = FALSE;
}

static t_process	*ft_abort(t_process *p)
{
	t_process *head;

	head = p;
	while (p && p->cmd)
	{
		if (p->grp)
			ft_close(p->pipe[0]);
		p = p->grp;
	}
	return (ft_free_tprocess(head));
}

t_process			*init_process(t_tree *t, t_shell *sh)
{
	t_process	*new;

	new = NULL;
	if ((new = (t_process *)malloc(sizeof(t_process))))
	{
		ft_init_fd(new, sh);
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
			if ((tmp->grp = init_process(t, sh)))
		 	{
		 		if (tmp->grp->cmd)
		 		{
		 			if (t->o_type == O_PIPE && t->next 
		 			&& (pipe(tmp->grp->pipe) < 0))
		 			{
		 				error("broken pipe", tmp->grp->cmd);
						return (ft_abort(head));
		 			}
				}
				else
				{
					error("command not found", *tmp->grp->argv);
					return (ft_abort(head));
				}
				tmp = tmp->grp;
			}
		}
	}
	else
	{
		if (!head->cmd)
			error("command not found", *head->argv);
		return (ft_abort(head));
	}
	return (head);
}
