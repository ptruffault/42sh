/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_open.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptruffau <ptruffau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/13 15:28:15 by ptruffau          #+#    #+#             */
/*   Updated: 2019/04/27 13:42:08 by fstadelw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/stat.h>
#include "libft.h"

int	ft_open(const char *path, int flag, mode_t mode)
{
	int			fd;
	struct stat	inf;

	fd = -1;
	if (lstat(path, &inf) == -1)
	{
		if (!(flag & O_CREAT))
			error("no such file or directory", path);
		else if ((fd = open(path, flag, mode)) < 0)
			error("can't open this file", path);
	}
	else
	{
		if (S_ISDIR(inf.st_mode))
			error("is a directory", path);
		else if (!(flag & O_CREAT) && !(inf.st_mode & S_IRUSR))
			error("permission denied", path);
		else if (S_ISLNK(inf.st_mode))
			error("ft_open do not follow symbolic link", path);
		else if ((fd = open(path, flag, mode)) < 0)
			error("can't open this file", path);
	}
	return (fd);
}
