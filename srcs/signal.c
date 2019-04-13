/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptruffau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/03 12:57:50 by ptruffau          #+#    #+#             */
/*   Updated: 2019/03/26 17:18:36 by stdenis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell42.h"

static const t_sig_msg	g_signal_msg[] = {
	{.sig = SIGHUP, .msg = "hanghup"},
	{.sig = SIGINT, .msg = "interupted"},
	{.sig = SIGQUIT, .msg = "quit"},
	{.sig = SIGILL, .msg = "illegal instruction"},
	{.sig = SIGTRAP, .msg = "trace/BPT trap"},
	{.sig = SIGABRT, .msg = "abort"},
	{.sig = SIGEMT, .msg = "emulate instruction executed"},
	{.sig = SIGFPE, .msg = "floating exception"},
	{.sig = SIGKILL, .msg = "killed"},
	{.sig = SIGBUS, .msg = "bus error"},
	{.sig = SIGSEGV, .msg = "segmentation fault"},
	{.sig = SIGSYS, .msg = "bad system call"},
	{.sig = SIGPIPE, .msg = "broken pipe"},
	{.sig = SIGALRM, .msg = "alarm clock"},
	{.sig = SIGTERM, .msg = "terminated"},
	{.sig = SIGURG, .msg = "SIGURP"},
	{.sig = SIGSTOP, .msg = "suspended"},
	{.sig = SIGTSTP, .msg = "suspended"},
	{.sig = SIGCONT, .msg = "continued"},
	{.sig = SIGCHLD, .msg = "SIGCHLD"},
	{.sig = SIGTTIN, .msg = "suspended (tty input)"},
	{.sig = SIGTTOU, .msg = "suspended (tty output)"},
	{.sig = SIGIO, .msg = "I/O is possible on a descriptor"},
	{.sig = SIGXCPU, .msg = "cpu time limit exceeded"},
	{.sig = SIGXFSZ, .msg = "file size limit exceeded"},
	{.sig = SIGPROF, .msg = "profiling time alarm"},
	{.sig = SIGVTALRM, .msg = "virtual time alarm"},
	{.sig = SIGUSR1, .msg = "user signal 1"},
	{.sig = SIGUSR2, .msg = "user signal 2"},
	{.msg = NULL}
};

static void	sig_handler(int sig)
{
	t_shell		*sh;

	sh = ft_get_set_shell(NULL);
	if (sig == SIGCHLD)
		ft_wait_background(sh);
	else if (sig == SIGWINCH)
		ft_update_windows(&sh->e);
}

int		ft_signal_check(t_process *p)
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

void	set_son_signal(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	signal(SIGTSTP, SIG_DFL);
	signal(SIGTTIN, SIG_DFL);
	signal(SIGTTOU, SIG_DFL);
	signal(SIGCHLD, SIG_DFL);
	signal(SIGWINCH, SIG_DFL);
}

void	set_signals(void)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGCHLD, sig_handler);
	signal(SIGWINCH, sig_handler);
	signal(SIGTSTP, SIG_IGN);
	signal(SIGTTIN, SIG_IGN);
	signal(SIGTTOU, SIG_IGN);
}
