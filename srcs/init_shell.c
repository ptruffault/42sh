/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptruffau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/08 12:08:41 by ptruffau          #+#    #+#             */
/*   Updated: 2019/03/19 11:43:05 by stdenis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <shell42.h>

static void	ft_null(t_shell *sh, char **envv)
{
	ft_get_set_shell(sh);
	sh->pid = getpid();
	sh->heredoc = 0;
	sh->interactive = FALSE;
	sh->intern = NULL;
	sh->clipboard = NULL;
	sh->alias = NULL;
	sh->txt = NULL;
	sh->process = NULL;
	sh->std[0] = STDIN_FILENO;
	sh->std[1] = STDOUT_FILENO;
	sh->std[2] = STDERR_FILENO;
	sh->env = init_tenvv(envv);
}

void		init_shell(t_shell *sh, char **envv, char **argv)
{
	ft_null(sh, envv);
	init_env(sh, argv);
	set_signals();
	if (!isatty(0))
	{
		if (exec_fd(sh, 0) == 0)
			error("abort", "no standart input");
		ft_exit("-1", sh);
	}
	if (argv[1] && !ft_isempty(argv[1]))
	{
		exec_file(argv[1], sh);
		ft_exit("-1", sh);
	}
	sh->interactive = TRUE;
	init_termcaps(sh);
}
