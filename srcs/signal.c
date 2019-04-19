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
	{.sig = SIGALRM, .msg = "alarm clock"},
	{.sig = SIGTERM, .msg = "terminated"},
	{.sig = SIGURG, .msg = "SIGURP"},
	{.sig = SIGSTOP, .msg = "suspended"},
	{.sig = SIGTSTP, .msg = "suspended (tty)"},
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
		ft_update_windows(&sh->e, true);
}

static void	ft_leave(int sig)
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
			error_i("42sh get killed by signal", i);
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

void		set_son_signal(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	signal(SIGTSTP, SIG_DFL);
	signal(SIGTTIN, SIG_DFL);
	signal(SIGTTOU, SIG_DFL);
	signal(SIGCHLD, SIG_DFL);
	signal(SIGWINCH, SIG_DFL);
	signal(SIGUSR1, SIG_DFL);
	signal(SIGUSR2, SIG_DFL);
	signal(SIGIO, SIG_DFL);
	signal(SIGILL, SIG_DFL);
	signal(SIGTRAP, SIG_DFL);
	signal(SIGABRT, SIG_DFL);
	signal(SIGEMT, SIG_DFL);
	signal(SIGFPE, SIG_DFL);
	signal(SIGBUS, SIG_DFL);
	signal(SIGSEGV, SIG_DFL);
	signal(SIGSYS, SIG_DFL);
	signal(SIGALRM, SIG_DFL);
	signal(SIGTERM, SIG_DFL);
	signal(SIGURG, SIG_DFL);
	signal(SIGXCPU, SIG_DFL);
	signal(SIGXFSZ, SIG_DFL);
	signal(SIGPROF, SIG_DFL);
	signal(SIGVTALRM, SIG_DFL);
}

void		set_signals(void)
{
	signal(SIGCHLD, sig_handler);
	signal(SIGWINCH, sig_handler);
	signal(SIGTSTP, SIG_IGN);
	signal(SIGINT, SIG_IGN);
	signal(SIGTTIN, SIG_IGN);
	signal(SIGTTOU, SIG_IGN);
	signal(SIGUSR1, SIG_IGN);
	signal(SIGUSR2, SIG_IGN);
	signal(SIGIO, ft_leave);
	signal(SIGILL, ft_leave);
	signal(SIGTRAP, ft_leave);
	signal(SIGABRT, ft_leave);
	signal(SIGEMT, ft_leave);
	signal(SIGFPE, ft_leave);
	signal(SIGBUS, ft_leave);
	signal(SIGSEGV, ft_leave);
	signal(SIGSYS, ft_leave);
	signal(SIGALRM, ft_leave);
	signal(SIGTERM, ft_leave);
	signal(SIGURG, ft_leave);
	signal(SIGXCPU, ft_leave);
	signal(SIGXFSZ, ft_leave);
	signal(SIGPROF, ft_leave);
	signal(SIGVTALRM, ft_leave);
}
