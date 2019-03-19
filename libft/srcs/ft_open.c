/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_open.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptruffau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/13 15:28:15 by ptruffau          #+#    #+#             */
/*   Updated: 2019/02/05 13:27:36 by adi-rosa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

int	ft_open(char *path, int flag, int mode)
{
	int fd;
	struct stat	inf;

	fd = -1;
	if (lstat(path, &inf) == -1)
		error("no such file or directory", path);
	else if (S_ISDIR(inf.st_mode))
		error("is a directory", path);
	else if (!(inf.st_mode & S_IRUSR))
		error("permission denied", path);
	else if (S_ISLNK(inf.st_mode))
		error("ft_open do not follow symbolic link", path);
	else if ((fd = open(path, flag, mode)) < 0)
		error("can't open this file", path);
	return (fd);
}
