/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_process.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptruffau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/18 15:17:06 by ptruffau          #+#    #+#             */
/*   Updated: 2019/03/26 17:21:55 by stdenis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell42.h"

static t_process	*ft_process_null(t_process *ret)
{
	ret->argv = NULL;
	ret->grp = NULL;
	ret->next = NULL;
	ret->cmd = NULL;
	ret->argv = NULL;
	ret->saved_env = NULL;
	ret->env = NULL;
	return (ret);
}

static t_process	*ft_new_process(t_shell *sh)
{
	t_process *ret;

	if (!(ret = (t_process *)malloc(sizeof(t_process))))
		return (NULL);
	ret->fd[0] = sh->std[0];
	ret->fd[1] = sh->std[1];
	ret->fd[2] = sh->std[2];
	ret->pgid = 0;
	ret->valid = 1;
	ret->sig = 0;
	ret->pipe[0] = -1;
	ret->pipe[1] = -1;
	ret->status = INIT;
	ret->ret = -1;
	ret->pid = -1;
	ret->builtins = FALSE;
	return (ft_process_null(ret));
}

static int			hash_or_path(t_process *ret, t_shell *sh)
{
	t_hash	*hash;

	if (!(hash = search_in_htable(*ret->argv, sh)))
	{
		if (!(ret->cmd = get_bin_path(*ret->argv, sh->env)))
			return (0);
		add_in_htable(*ret->argv, ret->cmd, sh);
	}
	else
	{
		if (!(ret->cmd = ft_strdup(hash->path)))
			return (0);
		hash->hit += 1;
	}
	return (1);
}

static	t_process	*ft_init_cmd(t_process *ret, t_tree *t, t_shell *sh)
{
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
	else if (hash_or_path(ret, sh))
	{
		sh->env = ft_new_envv(sh->env, "_", ret->argv[0], EXP);
		if (!(ret->env = tenvv_to_tab(sh->env)))
		{
			ft_get_envv_back(sh, ret, t);
			return (ft_free_tprocess(ret));
		}
	}
	return (ret);
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
		return (ft_init_cmd(ret, t, sh));
	}
	return (NULL);
}
