/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handle.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adi-rosa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/26 13:31:57 by adi-rosa          #+#    #+#             */
/*   Updated: 2019/04/26 13:31:58 by adi-rosa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <signal.h>
#include "shell42.h"

void		set_son_signal_bis(void)
{
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

void		set_signals_bis(void)
{
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
	signal(SIGHUP, SIG_DFL);
	signal(SIGIO, SIG_DFL);
	signal(SIGILL, SIG_DFL);
	signal(SIGTRAP, SIG_DFL);
	signal(SIGABRT, SIG_DFL);
	signal(SIGEMT, SIG_DFL);
	set_son_signal_bis();
}

void		set_signals(void)
{
	signal(SIGCHLD, sig_handler);
	signal(SIGWINCH, sig_handler);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGTSTP, SIG_IGN);
	signal(SIGINT, SIG_IGN);
	signal(SIGTTIN, SIG_IGN);
	signal(SIGTTOU, SIG_IGN);
	signal(SIGUSR1, SIG_IGN);
	signal(SIGUSR2, SIG_IGN);
	signal(SIGHUP, ft_leave);
	signal(SIGIO, ft_leave);
	signal(SIGILL, ft_leave);
	signal(SIGTRAP, ft_leave);
	signal(SIGABRT, ft_leave);
	signal(SIGEMT, ft_leave);
	set_signals_bis();
}
