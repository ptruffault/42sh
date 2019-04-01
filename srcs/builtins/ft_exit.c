/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exits.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptruffau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/08 13:09:39 by ptruffau          #+#    #+#             */
/*   Updated: 2019/03/26 17:21:55 by stdenis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell42.h"

int		ft_quit(int exit_code, t_shell *sh)
{
	kill_process(sh->process, SIGHUP, SUSPENDED);
	kill_process(sh->process, SIGHUP, RUNNING_FG);
	kill_process(sh->process, SIGHUP, RUNNING_BG);
	ft_free_tshell(sh);
	return (exit_code);
}

void	ft_exit(char *nbr, t_shell *sh)
{
	exit(ft_quit((nbr ? ft_atoi(nbr) : 0), sh));
}
