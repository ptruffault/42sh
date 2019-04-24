/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_history.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adi-rosa <adi-rosa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/01 17:47:37 by adi-rosa          #+#    #+#             */
/*   Updated: 2019/04/24 17:12:12 by fstadelw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "shell42.h"
#include "get_input.h"

int				ft_isparenth(char c)
{
	if (c == '{' || c == '(')
		return (1);
	else if (c == '}' || c == ')')
		return (2);
	return (0);
}

t_hist			*new_hist(void)
{
	t_hist	*n;

	if (!(n = (t_hist *)malloc(sizeof(t_hist))))
		return (NULL);
	n->s = NULL;
	n->nb = 0;
	n->next = NULL;
	n->prev = NULL;
	return (n);
}

t_hist			*init_hist(char *hist)
{
	t_hist	*ret;
	t_hist	*tmp;
	int		fd;
	char	*line;

	tmp = NULL;
	ret = NULL;
	if ((fd = ft_open(hist, O_RDWR | O_CREAT | O_NOFOLLOW | O_NONBLOCK, 511)) >= 0)
		while (get_next_line(fd, &line) == 1 && line)
		{
			if (!(tmp = new_hist()))
				return (ft_free_thist(ret));
			tmp->s = line;
			tmp->next = !ret ? NULL : ret;
			tmp->nb = !ret ? 1 : ret->nb + 1;
			if (tmp->next)
				tmp->next->prev = tmp;
			ret = tmp;
			if (tmp->nb >= ft_get_hist_size())
				break ;
		}
	ft_close(fd);
	return (tmp);
}
