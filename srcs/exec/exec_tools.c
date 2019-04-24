/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_tools.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptruffau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/16 11:10:18 by ptruffau          #+#    #+#             */
/*   Updated: 2019/04/16 11:10:20 by ptruffau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell42.h"

int		check_exe(char *bin_path)
{
	struct stat inf;

	if ((stat(bin_path, &inf)) != -1 && inf.st_mode & S_IFREG)
	{
		if (inf.st_mode & S_IXUSR && access(bin_path, X_OK) != -1)
			return (1);
		else
			return (error("permission denied", bin_path));
	}
	else
		return (error("not an executable", bin_path));
}

void	ft_exit_son(t_shell *sh, int exit_code, t_process *p)
{
	ft_close(p->fd[0]);
	ft_close(p->fd[1]);
	ft_close(p->fd[2]);
	ft_free_tshell(sh);
	ft_free_tree(ft_get_set_tree(NULL));
	exit(exit_code);
}

void	ft_link_process_to_term(t_process *p, t_shell *sh)
{
	if (sh->interactive == TRUE && p && p->background == FALSE && p->pid != 0)
		ft_tcsetpgrp(sh->std[0], p->pgid);
	else if (sh->interactive == TRUE && p && p->background == TRUE)
		sh->env = ft_new_envv_int(sh->env, "!", p->pid, IN);
}
