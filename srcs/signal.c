/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptruffau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/03 12:57:50 by ptruffau          #+#    #+#             */
/*   Updated: 2018/12/03 12:57:51 by ptruffau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell42.h"
#include "../includes/get_input.h"

t_process	*ft_wait_background(t_process *p)
{
	t_process *tmp;

	tmp = p;
	while (tmp)
	{
		if (tmp->status == RUNNING_BG && tmp->pid > 0
		&& waitpid(tmp->pid, &tmp->ret, WUNTRACED | WNOHANG) >= 0)
		{
			tmp->status = DONE;
			ft_printf("{%i} %s \033[1;32mdone\033[00m\n", tmp->pid, tmp->cmd);
			return (tmp);
		}
		tmp = tmp->next;
	}
	return (NULL);
}

void		sig_handler(int sig)
{
	t_shell		*sh;

	sh = ft_get_set_shell(NULL);
	if (sig == SIGINT && !(sh && sh->process
	&& kill_running_process(sh->process, SIGINT, RUNNING_FG)))
		ft_disp(sh);
	if (sig == SIGWINCH && sh)
		ft_update_windows(&sh->e);
	if (sig == SIGTSTP && sh && sh->process)
		kill_running_process(sh->process, SIGTSTP, RUNNING_FG);
	if (sig == SIGCHLD && sh && sh->process)
		ft_wait_background(sh->process);
	if ((sig == SIGTTIN || sig == SIGTTOU)
	&& (kill_running_process(sh->process, SIGKILL, RUNNING_BG)))
	{
		ft_printf("SIGttIN");
	}
	if (sig == SIGKILL)
		ft_exit("9");
}

void		set_signals(void)
{
	signal(SIGINT, sig_handler);
	signal(SIGTSTP, sig_handler);
	signal(SIGCHLD, sig_handler);
	signal(SIGWINCH, sig_handler);
	signal(SIGKILL, sig_handler);
	signal(SIGTTIN, sig_handler);
	signal(SIGTTOU, sig_handler);
}
