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

static int	ft_check_alpha(char *input)
{
	int i;

	i = 0;
	while (input[i])
		if (!ft_isalpha(input[i++]))
			return (0);
	return (1);
}


int			ft_quit(int exit_code, t_shell *sh)
{
	if (exit_code == -1)
		exit_code = ft_atoi(get_tenvv_val(sh->env, "?"));
	kill_process(sh->process, SIGHUP, SUSPENDED);
	kill_process(sh->process, SIGHUP, RUNNING_FG);
	kill_process(sh->process, SIGHUP, RUNNING_BG);
	ft_deload_hist_in_file(sh);
	cleaning_htable(NULL, sh);
	free(sh->htable);
	ft_free_tshell(sh);
	return (exit_code);
}

void		ft_exit(char *nbr, t_shell *sh)
{
	int ret;

	ret = 0;
	if (ft_check_alpha(nbr))
		ret = 255;
	else if ((ret = ft_atoi(nbr) < 0))
		ret = 255;
	exit(ft_quit(ret, sh));
}
