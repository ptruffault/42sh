/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
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
	while (input && input[i])
		if (!ft_isdigit(input[i++]))
			return (0);
	return (1);
}

int			ft_quit(int exit_code, t_shell *sh)
{
	if (exit_code == -1)
		exit_code = ft_atoi(get_tenvv_val(sh->env, "?"));
	kill_process(sh->process, SIGKILL, RUNNING_FG);
	ft_deload_hist_in_file(sh);
	cleaning_htable(NULL, sh);
	free(sh->htable);
	ft_free_tshell(sh);
	return (exit_code);
}

int			ft_exit(char **nbr, t_shell *sh)
{
	int ret;

	ret = -1;
	if (nbr && nbr[0] != NULL && nbr[1] != NULL)
	{
		error("too many arguments", NULL);
		sh->env = ft_new_envv_int(sh->env, "?", 1, IN);
		return (1);
	}
	else if (nbr && *nbr && (!ft_check_alpha(*nbr)
		|| (ret = ft_atoi(*nbr)) < 0))
	{
		error("numeric argument required", NULL);
		ret = 255;
	}
	exit(ft_quit(ret, sh));
	return (ret);
}
