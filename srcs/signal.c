/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptruffau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/03 12:57:50 by ptruffau          #+#    #+#             */
/*   Updated: 2019/03/19 13:49:05 by stdenis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <shell42.h>
#include "../includes/get_input.h"

void		sig_handler(int sig)
{
	t_shell		*sh;

	if ((sh = ft_get_set_shell(NULL)))
	{
		if (sig == SIGINT)
		{
			if (sh->interactive == TRUE && !kill_process(sh->process, SIGINT, RUNNING_FG))
				ft_disp(sh);
			else if (sh->interactive == FALSE)
				ft_exit("2", sh);
		}
		else if (sig == SIGWINCH && sh)
			ft_update_windows(&sh->e);
		else if (sig == SIGTSTP && sh && sh->process)
			kill_process(sh->process, SIGTSTP, RUNNING_FG);
		else if (sig == SIGCHLD && sh && sh->process)
			ft_wait_background(sh);
	}
}

void		set_signals(void)
{
	signal(SIGINT, sig_handler);
	signal(SIGTSTP, sig_handler);
	signal(SIGCHLD, sig_handler);
	signal(SIGWINCH, sig_handler);
}
