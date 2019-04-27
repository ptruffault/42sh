/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptruffau <ptruffau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/08 13:09:39 by ptruffau          #+#    #+#             */
/*   Updated: 2019/04/24 17:00:51 by fstadelw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include "shell42.h"

static int	ft_check_alpha(char *input)
{
	int i;

	i = -1;
	while (input && input[++i])
		if (input[i] != '-' && input[i] != '+' && !ft_isdigit(input[i]))
			return (0);
	return (1);
}

int			ft_quit(int exit_code, t_shell *sh)
{
	if (get_tenvv_val(sh->env, "?") == NULL)
		exit_code = 2;
	if (exit_code == 226)
		exit_code = ft_atoi(get_tenvv_val(sh->env, "?"));
	if (sh->interactive == TRUE && isatty(0) && isatty(1))
		ft_set_old_term(sh, 0);
	if (isatty(0) && isatty(1))
		kill_process(sh->process, SIGKILL, RUNNING_FG);
	ft_deload_hist_in_file(sh);
	cleaning_htable(sh);
	free(sh->htable);
	ft_free_tshell(sh);
	return (exit_code);
}

int			ft_exit(char **nbr, t_shell *sh)
{
	int ret;

	ret = 226;
	if (nbr && nbr[0] != NULL && nbr[1] != NULL)
	{
		error("too many arguments", NULL);
		sh->env = ft_new_envv_int(sh->env, "?", 1, IN);
		return (1);
	}
	else if (nbr && *nbr && (!ft_check_alpha(*nbr)))
	{
		error("numeric argument required", NULL);
		ret = 2;
	}
	else if (nbr && *nbr && (ret = ft_atoi(*nbr)) < 0 && *nbr[0] != '-')
	{
		error("numeric argument required", NULL);
		ret = 2;
	}
	exit(ft_quit(ret, sh));
	return (ret);
}
