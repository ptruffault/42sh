/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptruffau <ptruffau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/03 12:57:50 by ptruffau          #+#    #+#             */
/*   Updated: 2019/04/24 16:46:04 by fstadelw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <signal.h>
#include "shell42.h"

static const t_sig_msg	g_signal_msg[] = {
	{SIGHUP, "hanghup"},
	{SIGINT, "interupted"},
	{SIGQUIT, "quit"},
	{SIGILL, "illegal instruction"},
	{SIGTRAP, "trace/BPT trap"},
	{SIGABRT, "abort"},
	{SIGEMT, "emulate instruction executed"},
	{SIGFPE, "floating exception"},
	{SIGKILL, "killed"},
	{SIGBUS, "bus error"},
	{SIGSEGV, "segmentation fault"},
	{SIGSYS, "bad system call"},
	{SIGALRM, "alarm clock"},
	{SIGTERM, "terminated"},
	{SIGURG, "SIGURP"},
	{SIGSTOP, "suspended"},
	{SIGTSTP, "suspended (tty)"},
	{SIGCONT, "continued"},
	{SIGCHLD, "SIGCHLD"},
	{SIGTTIN, "suspended (tty input)"},
	{SIGTTOU, "suspended (tty output)"},
	{SIGIO, "I/O is possible on a descriptor"},
	{SIGXCPU, "cpu time limit exceeded"},
	{SIGXFSZ, "file size limit exceeded"},
	{SIGPROF, "profiling time alarm"},
	{SIGVTALRM, "virtual time alarm"},
	{SIGUSR1, "user signal 1"},
	{SIGUSR2, "user signal 2"},
	{0, NULL}
};

void		sig_handler(int sig)
{
	t_shell		*sh;

	sh = ft_get_set_shell(NULL);
	if (sig == SIGPIPE)
		ft_putendl("HERE I AM SIG PIPE");
	if (sig == SIGCHLD)
		ft_wait_background(sh);
	else if (sig == SIGWINCH)
		ft_update_windows(&sh->e, true);
}

void		ft_leave(int sig)
{
	t_shell *sh;
	int		i;

	i = 0;
	sh = ft_get_set_shell(NULL);
	ft_set_old_term(sh, 0);
	while (g_signal_msg[i].msg != NULL)
	{
		if (g_signal_msg[i].sig == sig)
		{
			error_i("42sh get killed by signal", sig);
			ft_putendl(g_signal_msg[i].msg);
			break ;
		}
		i++;
	}
	exit(ft_quit(sig + 128, sh));
}

int			ft_signal_check(t_process *p)
{
	int i;

	i = 0;
	if (p->sig <= 0)
		return (0);
	while (g_signal_msg[i].msg != NULL)
	{
		if (g_signal_msg[i].sig == p->sig)
		{
			ft_putstr_fd(g_signal_msg[i].msg, 2);
			return (1);
		}
		i++;
	}
	return (0);
}
