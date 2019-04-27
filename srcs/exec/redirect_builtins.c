/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_builtins.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptruffau <ptruffau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/08 14:17:51 by ptruffau          #+#    #+#             */
/*   Updated: 2019/04/24 16:53:25 by fstadelw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <signal.h>
#include "shell42.h"
#include "ft_printf.h"

static void	ft_close_red(t_redirect *r, t_process *p, t_shell *sh)
{
	while (r)
	{
		if ((ft_isstd(sh->std[0]) ||  sh->std[0] != r->from)
			&& (ft_isstd(sh->std[1]) || sh->std[1] != r->from)
			&& (ft_isstd(sh->std[2]) ||  sh->std[2] != r->from)
			&& r->to == -1 && (!p || p->fd[r->from] == -1))
			ft_close(r->from);
		r = r->next;
	}
}

int			ft_redirect_builtin(t_tree *t, t_process *p, t_shell *sh)
{
	t_redirect *r;

	r = t->r;
	if (!p)
		signal(SIGINT, sig_handler);
	while (r)
	{
		if (!get_destination_fd(r))
			return (0);
		if (ft_isstd(r->from) && ft_isstd(sh->std[r->from]))
			sh->std[r->from] = dup(r->from);
		if (ft_isstd(r->to) && ft_isstd(sh->std[r->to]))
			sh->std[r->to] = dup(r->to);
		if (fd_dup(r->to, r->from, p) < 0)
			return (0);
		if (p && ft_isstd(r->from))
			p->fd[r->from] = r->to;
		r = r->next;
	}
	ft_close_red(t->r, p, sh);
	return (1);
}

void		ft_reset_fd(t_shell *sh)
{
	int	i;
	int std[3];

	i = -1;
	std[0] = STDIN_FILENO;
	std[1] = STDOUT_FILENO;
	std[2] = STDERR_FILENO;
	while (++i <= 2)
	{
		if (sh->std[i] != std[i])
		{
			if (dup2(sh->std[i], std[i]) < 0)
				error_i("can't load old fd", i);
			ft_close(sh->std[i]);
			sh->std[i] = std[i];
		}
	}
}
