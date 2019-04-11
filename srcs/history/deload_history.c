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
	int fd;

	hist = sh->hist;
	if (hist)
	{
		while (hist->next)
			hist = hist->next;
		if (!(path = get_tenvv_val(sh->env, "HISTFILE")))
			return ;
		unlink(path);
		if ((fd = ft_open(path, O_RDWR | O_CREAT | O_NOFOLLOW, 0644)) < 0)
			return ;
		while (hist)
		{
			ft_putendl_fd(hist->s, fd);
			hist = hist->prev;
		}
		ft_close(fd);
	}
}
