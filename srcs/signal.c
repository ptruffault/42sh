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
		&& waitpid(tmp->pid, &tmp->ret, WUNTRACED | WNOHANG) > 0)
		{
			tmp->status = DONE;
			ft_printf("{%i} \033[1;32mdone\033[00m  %s ~> %i\n", tmp->pid, tmp->cmd, tmp->ret);
			return (tmp);
		}
		tmp = tmp->next;
	}
	return (NULL);
}

void		sig_handler(int sig)
{
	t_shell		*sh;

	if ((sh = ft_get_set_shell(NULL)))
	{
		if (sig == SIGINT && !kill_running_process(sh->process, SIGINT, RUNNING_FG))
				ft_disp(sh);
		else if (sig == SIGWINCH && sh)
			ft_update_windows(&sh->e);
		else if (sig == SIGTSTP && sh && sh->process)
			kill_process(sh->process, SIGTSTP, RUNNING_FG);
		else if (sig == SIGCHLD && sh && sh->process)
			ft_wait_background(sh->process);
	}
}

void		set_signals(void)
{
	signal(SIGINT, sig_handler);
	signal(SIGTSTP, sig_handler);
	signal(SIGCHLD, sig_handler);
	signal(SIGWINCH, sig_handler);
	signal(SIGTTIN, sig_handler);
	signal(SIGTTOU, sig_handler);
}
