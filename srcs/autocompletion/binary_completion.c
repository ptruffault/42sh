/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   binary_completion.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stdenis <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/18 15:33:46 by stdenis           #+#    #+#             */
/*   Updated: 2019/03/26 17:18:36 by stdenis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <dirent.h>
#include "shell42.h"

int			fill_tabl_binary(DIR *fd, char ***tabl, char *value, char *path)
{
	static int				j;
	struct dirent	*dir;

	while (fd && (dir = readdir(fd)))
	{
		if (!(ft_strequ(dir->d_name, "."))
			&& !(ft_strequ(dir->d_name, "..")))
		{
			if ((ft_str_startwith(dir->d_name, value)) &&
				check_exec(dir->d_name, path))
			{
				j++;
				if (add_to_tabl(tabl, dir->d_name, j))
					return (-1);
			}
		}
	}
	return (j);
}

int			fill_tabl_all_bin(DIR *fd, char ***tabl, char *path)
{
	static int				j;
	struct dirent	*dir;

	while (fd && (dir = readdir(fd)))
	{
		if (!(ft_strequ(dir->d_name, "."))
			&& !(ft_strequ(dir->d_name, "..")))
		{
			if (check_exec(dir->d_name, path))
			{
				j++;
				if (add_to_tabl(tabl, dir->d_name, j))
					return (-1);
			}
		}
	}
	return (j);
}

char		**get_binary(char **path, char *value, bool all, int *total)
{
	int				i;
	int				j;
	char			**tabl;
	DIR				*fd;

	i = -1;
	j = 0;
	if (!(tabl = (char**)malloc(sizeof(char*) * 2)))
		return (NULL);
	tabl[j] = NULL;
	while (path[++i])
	{
		fd = opendir(path[i]);
		if (!all)
			j = fill_tabl_binary(fd, &tabl, value, path[i]);
		else
			j = fill_tabl_all_bin(fd, &tabl, path[i]);
		closedir(fd);
	}
	*total += j;
	return (tabl);
}
