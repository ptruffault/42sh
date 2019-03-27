/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_process.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptruffau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/18 15:17:06 by ptruffau          #+#    #+#             */
/*   Updated: 2019/03/20 18:11:13 by stdenis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <shell42.h>

static t_process 	*ft_new_process(t_shell *sh)
{
	t_process *ret;

	if (!(ret = (t_process *)malloc(sizeof(t_process))))
		return (NULL);
	ret->fd[0] = sh->std[0];
	ret->fd[1] = sh->std[1];
	ret->fd[2] = sh->std[2];
	ret->pgid = 0;
	ret->sig = 0;
	ret->pipe[0] = -1;
	ret->pipe[1] = -1;
	ret->status = INIT;
	ret->ret = -1;
	ret->argv = NULL;
	ret->grp = NULL;
	ret->next = NULL;
	ret->cmd = NULL;
	ret->argv = NULL;
	ret->pid = -1;
	ret->saved_env = NULL;
	ret->env = NULL;
	ret->builtins = FALSE;
	return (ret);
}

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

void			ft_get_envv_back(t_shell *sh, t_process *p, t_tree *t)
{
	if (t->assign)
	{
		sh->env = ft_pull_tenvv(sh->env, t->assign);
		sh->env = ft_push_tenvv(sh->env, p->saved_env);
		p->saved_env = ft_free_tenvv(p->saved_env);
	}	
}

void ft_setup_localenv(t_process *p, t_shell *sh, t_tree *t)
{
	if (t->assign)
	{
		if (sh->env && !(p->saved_env = ft_tenvv_cpy(sh->env)))
			error("can't save environnement", NULL);
		sh->env = ft_push_tenvv(sh->env, t->assign);
	}
}

t_process			*init_process(t_tree *t, t_shell *sh)
{
	t_process	*ret;

	if ((ret = ft_new_process(sh)))
	{
		ft_setup_localenv(ret, sh, t);
		ret->background = (t->o_type == O_BACK ? TRUE : FALSE);
		ret->status = (ret->background == TRUE ? RUNNING_BG : RUNNING_FG);
		if (!(ret->argv = ft_twordto_arr(t->cmd)))
		{
			ft_get_envv_back(sh, ret, t);
			return (ft_free_tprocess(ret));
		}
		if (check_builtin(*ret->argv))
		{
			ret->builtins = TRUE;
			ret->pid = 0;
			if (!(ret->cmd = ft_strdup(*ret->argv)))
			{
				ft_get_envv_back(sh, ret, t);
				return (ft_free_tprocess(ret));
			}
		}
		else if ((ret->cmd = get_bin_path(*ret->argv, sh->env)))
		{
			sh->env = ft_new_envv(sh->env, "_", ret->cmd);
			ret->env = tenvv_to_tab(sh->env);
		}
		return (ret);
	}
	return (NULL);
}

t_process *init_pipe_process(t_tree *t, t_shell *sh)
{
	t_process *head;
	t_process *tmp;

	head = NULL;
	if ((head = init_process(t, sh)) && !pipe(head->pipe))
	{
		tmp = head;
		if (!head->cmd)
			return (ft_abort(head, "command not found", head));
		while (t->o_type == O_PIPE)
		{	
			t = t->next;
			if (t && (tmp->grp = init_process(t, sh)))
		 	{
		 		tmp = tmp->grp;
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
	}
	return (head);
}
