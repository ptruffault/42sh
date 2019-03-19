/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptruffau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/12 15:43:08 by ptruffau          #+#    #+#             */
/*   Updated: 2018/01/16 15:12:12 by ptruffau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

static	int		ft_check_charriot(char *buff, char **res)
{
	char	*tmp;
	char	*tofree;
	char	*s;

	tofree = *res;
	s = buff;
	if ((tmp = ft_strchr(buff, '\n')) != NULL)
		s = ft_strsub(buff, 0, tmp - buff);
	if (!(*res = ft_strjoin(*res, s)))
	{
		ft_strdel(&tofree);
		if (tmp != NULL)
			ft_strdel(&s);
		return (-1);
	}
	ft_strdel(&tofree);
	if (tmp != NULL)
	{
		ft_strdel(&s);
		ft_strcpy(buff, tmp + 1);
		return (1);
	}
	return (0);
}

int				get_next_line(const int fd, char **line)
{
	static char		buff[BUFF_SIZE + 1];
	int				i;

	if (fd < 0 || line == NULL)
		return (-1);
	if (!(*line = ft_strnew(0)))
		return (-1);
	if (ft_strlen(buff) > 0)
		if (ft_check_charriot(buff, line) == 1)
			return (1);
	while ((i = read(fd, buff, BUFF_SIZE)) > 0)
	{
		buff[i] = '\0';
		if (ft_check_charriot(buff, line) == 1)
			return (1);
	}
	if (ft_strlen(buff) == 0)
	{
		ft_strdel(line);
		return (i);
	}
	ft_memset(buff, 0, 1);
	return (1);
}
