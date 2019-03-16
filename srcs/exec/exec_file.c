/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptruffau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/08 13:59:48 by ptruffau          #+#    #+#             */
/*   Updated: 2019/02/18 13:49:57 by adi-rosa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <shell42.h>

int		exec_fd(t_shell *sh, int fd)
{
	int		i;
	t_tree	*t;

	i = 0;
	while (get_next_line(fd, &sh->txt) == 1 && sh->txt && *sh->txt && !ft_isempty(sh->txt))
	{
		i++;
		if (*sh->txt != '#'
		&& (t = get_tree(sh->txt)))
			ft_free_tree(exec_tree(t, sh));
		ft_strdel(&sh->txt);
	}
	get_next_line(-1, NULL);
	return (i);
}

int		exec_file(char *path, t_shell *sh)
{
	int		fd;

	if ((fd = open(path, O_RDWR, S_IRWXU)) >= 0)
	{
		exec_fd(sh, fd);
		ft_close(fd);
	}
	else
	{
		error("can't exec this file", path);
		return (-1);
	}
	return (0);
}
