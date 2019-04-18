/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptruffau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/13 13:23:52 by ptruffau          #+#    #+#             */
/*   Updated: 2019/03/26 17:21:55 by stdenis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <get_input.h>

static int		ft_init_input_link(t_shell *sh, t_hist *tmp)
{
	sh->e.hist = tmp;
	if (sh->hist)
	{
		tmp->next = sh->hist;
		tmp->next->prev = tmp;
	}
	tmp->nb = !sh->hist ? 1 : sh->hist->nb + 1;
	if (!(tmp->s = ft_strnew(2)))
	{
		free(tmp);
		if (sh->hist)
			sh->hist->prev = NULL;
		return (FAILURE);
	}
	return (SUCCESS);
}

int				ft_get_hist_size(void)
{
	t_shell	*sh;
	char	*line;

	sh = ft_get_set_shell(NULL);
	if (!(line = get_tenvv_val(sh->env, "HISTSIZE")))
		return (32767);
	return (ft_atoi(line) > 32767 ? ft_atoi(line) : 32767);
}

static int		hist_init_for_gi(t_shell *sh)
{
	t_hist *tmp;

	tmp = sh->hist;
	while (tmp->next)
		tmp = tmp->next;
	tmp->prev->next = NULL;
	tmp->prev = NULL;
	tmp->next = sh->hist;
	ft_strdel(&tmp->s);
	if (!(tmp->s = ft_strnew(3)))
	{
		free(tmp);
		return (FAILURE);
	}
	sh->hist->prev = tmp;
	sh->e.hist = tmp;
	tmp->nb = sh->hist->nb + 1;
	return (SUCCESS);
}

int				init_tedit(t_shell *sh)
{
	t_hist *tmp;

	ft_init_print_modes(&sh->e, 0);
	ft_update_windows(&sh->e, false);
	sh->e.edited = FALSE;
	sh->e.hist_size = ft_get_hist_size();
	sh->e.curr = 0;
	sh->e.pos = 0;
	sh->e.tmp = NULL;
	sh->e.pos_z = 0;
	sh->e.pos_y = 0;
	sh->e.select = -1;
	sh->e.select_pos = 0;
	sh->e.mode = 0;
	sh->e.hist = NULL;
	sh->e.incr_search = NULL;
	sh->e.head = NULL;
	if (sh->hist && sh->e.hist_size <= sh->hist->nb)
	{
		if (hist_init_for_gi(sh) == FAILURE)
			return (FAILURE);
	}
	else if (!(tmp = new_hist()) || ft_init_input_link(sh, tmp) == FAILURE)
		return (FAILURE);
	return (SUCCESS);
}
