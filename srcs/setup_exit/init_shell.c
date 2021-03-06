/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptruffau <ptruffau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/08 12:08:41 by ptruffau          #+#    #+#             */
/*   Updated: 2019/04/24 16:49:55 by fstadelw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <sys/ioctl.h>
#include <signal.h>
#include "shell42.h"

static void	ft_null(t_shell *sh)
{
	ft_get_set_shell(sh);
	sh->pid = getpid();
	sh->heredoc = 0;
	sh->fd = 0;
	sh->fc = FALSE;
	sh->err = 0;
	sh->jobs = NULL;
	sh->interactive = FALSE;
	sh->clipboard = NULL;
	sh->alias = NULL;
	sh->txt = NULL;
	sh->hist = NULL;
	sh->process = NULL;
	sh->exp_leave = 0;
	sh->std[0] = STDIN_FILENO;
	sh->std[1] = STDOUT_FILENO;
	sh->std[2] = STDERR_FILENO;
	sh->pgid = 0;
	sh->env = NULL;
	sh->htable = init_htable();
}

pid_t		ft_tcgetpgrp(int fd)
{
	int pgrp;

	if (ioctl(fd, TIOCGPGRP, &pgrp) < 0)
	{
		error("can't get pgid", "tcgetpgrp");
		return (-1);
	}
	return (pgrp);
}

int			ft_tcsetpgrp(int fd, pid_t pgrp)
{
	int pgrp_int;

	pgrp_int = pgrp;
	return (ioctl(fd, TIOCSPGRP, &pgrp_int));
}

int			ft_init_groups(t_shell *sh)
{
	while (ft_tcgetpgrp(STDIN_FILENO) != (sh->pgid = getpgrp()))
		kill(-sh->pgid, SIGTTIN);
	sh->pgid = getpid();
	if (setpgid(sh->pgid, sh->pgid) < 0)
		return (error("setpgid failed", NULL));
	if (ft_tcsetpgrp(STDIN_FILENO, sh->pgid) < 0)
		return (0);
	return (1);
}

int			init_shell(t_shell *sh, char **envv, char **argv)
{
	ft_null(sh);
	if (!(init_env(sh, argv, envv)))
		return (0);
	if (!isatty(0))
	{
		if (exec_fd(sh, 0) == 0)
			error("abort", "no standart input");
		return (0);
	}
	sh->interactive = TRUE;
	if (!ft_init_groups(sh) || !init_termcaps(sh))
		return (0);
	set_signals();
	return (1);
}
