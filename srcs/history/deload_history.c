/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deload_history.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adi-rosa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/05 12:33:19 by adi-rosa          #+#    #+#             */
/*   Updated: 2019/04/05 12:33:20 by adi-rosa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell42.h"

void	ft_deload_hist_in_file(t_shell *sh)
{
	t_hist	*hist;
	char	*path;

	hist = sh->hist;
	while (hist->next)
		hist = hist->next;
	if (!(path = get_tenvv_val(sh->env, "HISTFILE")))
		return ;
	unlink(path);
	while (hist)
	{
			ft_write_in_file(path, hist->s);
		hist = hist->prev;
	}
}
