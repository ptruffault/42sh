/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_builtin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptruffau <ptruffau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/04 14:13:40 by ptruffau          #+#    #+#             */
/*   Updated: 2019/04/24 17:00:14 by fstadelw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "shell42.h"

static int	job_control(char **argv, t_shell *sh)
{
	if (sh->interactive == TRUE && sh->process->background == FALSE
	&& sh->pid == getpid())
	{
		if (ft_strequ(*argv, "fg"))
			return (ft_fg(sh, argv));
		else if (ft_strequ(*argv, "bg"))
			return (ft_bg(sh, argv));
	}
	error("no job control", NULL);
	return (1);
}

static int	change_envv(char **argv, t_shell *sh)
{
	if (ft_strequ(*argv, "unset") && argv[1])
		sh->env = ft_unsetenv(sh->env, &argv[1]);
	else if (ft_strequ(*argv, "cd"))
		return (ft_cd(argv, sh));
	else if (ft_strequ(*argv, "export"))
		return (ft_export(sh, &argv[1]));
	else if (ft_strequ(*argv, "set"))
		ft_puttenvv(sh->env, IN, 0);
	else if (ft_strequ(*argv, "alias"))
		return (ft_alias(sh, argv));
	else if (ft_strequ(*argv, "unalias") && argv[1])
		sh->alias = ft_unsetenv(sh->alias, &argv[1]);
	return (0);
}

int			run_builtin(t_tree *t, t_process *p, t_shell *sh)
{
	char	**argv;

	argv = p->argv;
	if (ft_strequ(*argv, "exit"))
		return (ft_exit(&argv[1], sh));
	else if (ft_strequ(*argv, "echo"))
		return (ft_echo(&argv[1], p));
	else if (ft_strequ(*argv, "type"))
		return (ft_type(t->cmd->next));
	else if (ft_strequ(*argv, "jobs"))
		return (ft_jobs(sh, argv));
	else if (ft_strequ(*argv, "hi"))
		return (ft_hi(sh));
	else if (ft_strequ(*argv, "test"))
		return (ft_test(argv));
	else if (ft_strequ(*argv, "fc"))
		return (ft_fc(sh, argv));
	else if (ft_strequ(*argv, "bg") || ft_strequ(*argv, "fg"))
		return (job_control(argv, sh));
	else if (ft_strequ(*argv, "hash"))
		return (builtin_htable(&argv[1], sh));
	return (change_envv(argv, sh));
}
