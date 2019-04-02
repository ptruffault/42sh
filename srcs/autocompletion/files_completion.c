/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files_completion.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stdenis <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/18 15:33:46 by stdenis           #+#    #+#             */
/*   Updated: 2019/03/26 17:18:36 by stdenis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell42.h"

int			fill_tabl_files(DIR *fd, char ***tabl, char *value)
{
	static int				j;
	struct dirent	*dir;

	while (fd && (dir = readdir(fd)))
	{
		if ((ft_str_startwith(dir->d_name, value)))
		{
			j++;
			if (add_to_tabl(tabl, dir->d_name, j))
				return (-1);
		}
	}
	return (j);
}

int			fill_tabl_all_files(DIR *fd, char ***tabl)
{
	static int				j;
	struct dirent	*dir;

	while (fd && (dir = readdir(fd)))
	{
		if (!(ft_strnequ(dir->d_name, ".", 1)))
		{
			j++;
			if (add_to_tabl(tabl, dir->d_name, j))
				return (-1);
		}
	}
	return (j);
}

char		**get_files(char *value, bool all, int *total)
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
	fd = opendir(".");
	if (!all)
		j = fill_tabl_files(fd, &tabl, value);
	else
		j = fill_tabl_all_files(fd, &tabl);
	closedir(fd);
	*total += j;
	return (tabl);
}
