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

int			fill_tabl_files(DIR *fd, char ***tabl, char *value, int *j)
{
	struct dirent	*dir;

	while (fd && (dir = readdir(fd)))
	{
		if ((ft_strlen(value) == 0 && !(ft_strnequ(dir->d_name, ".", 1)))
			|| (ft_strlen(value) > 0 && (ft_str_startwith(dir->d_name, value))))
		{
			*j += 1;
			if (add_to_tabl(tabl, dir->d_name, *j))
				return (-1);
		}
	}
	return (*j);
}

int			fill_tabl_all_files(DIR *fd, char ***tabl, int *j)
{
	struct dirent	*dir;

	while (fd && (dir = readdir(fd)))
	{
		if (!(ft_strnequ(dir->d_name, ".", 1)))
		{
			*j += 1;
			if (add_to_tabl(tabl, dir->d_name, *j))
				return (-1);
		}
	}
	return (*j);
}

char		*which_file(char *value, DIR **fd)
{
	char			*tmp;

	if (ft_strequ(value, "/"))
	{
		*fd = opendir(value);
		value = value + 1;
		return (value);
	}
	if ((tmp = ft_strchr_end(value, '/')))
	{
		if (value - tmp == 0)
		{
			*fd = opendir("/");
			tmp[0] = '\0';
			tmp = tmp + 1;
		}
		else
		{
			tmp[0] = '\0';
			tmp = tmp + 1;
			*fd = opendir(value);
		}
		return (tmp);
	}
	*fd = opendir(".");
	return (value);
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
	value = which_file(value, &fd);
	if (!all)
		j = fill_tabl_files(fd, &tabl, value, &j);
	else
		j = fill_tabl_all_files(fd, &tabl, &j);
	if (fd != NULL)
		closedir(fd);
	if (j == -1 && (*total = 0))
		ft_arrdel(&tabl);
	*total = j;
	return (tabl);
}
