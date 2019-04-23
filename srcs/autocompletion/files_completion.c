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

static int	check_directory(char *file, char *path)
{
	char		*tmp;
	struct stat	file_stat;

	if (!path || !(tmp = ft_strjoin(path, "/")))
		return (0);
	if ((tmp = ft_strappend(&tmp, file)))
	{
		if ((stat(tmp, &file_stat)) < 0)
		{
			ft_strdel(&tmp);
			return (0);
		}
		if (S_ISDIR(file_stat.st_mode))
		{
			ft_strdel(&tmp);
			return (1);
		}
		ft_strdel(&tmp);
		return (0);
	}
	return (0);
}

static char	*which_file(char *value, DIR **fd, char **path)
{
	char			*tmp;

	*path = value;
	if (ft_strequ(value, "/"))
	{
		*fd = opendir(value);
		return (value + 1);
	}
	if ((tmp = ft_strchr_end(value, '/')))
	{
		tmp[0] = '\0';
		if (value - tmp == 0)
		{
			*fd = opendir("/");
			*path = "/";
		}
		else
			*fd = opendir(value);
		return (tmp + 1);
	}
	*fd = opendir(".");
	*path = "./";
	return (value);
}

static int	fill_tabl_files(DIR **fd, char ***tabl, char *value, int *j)
{
	struct dirent	*dir;
	char			*tmp;
	char			*path;

	value = which_file(value, fd, &path);
	while (*fd && (dir = readdir(*fd)))
		if ((ft_strlen(value) == 0 && !(ft_strnequ(dir->d_name, ".", 1)))
			|| (ft_strlen(value) > 0 && (ft_str_startwith(dir->d_name, value))))
		{
			*j += 1;
			if (check_directory(dir->d_name, path))
			{
				tmp = ft_strjoin(dir->d_name, "/");
				if (add_to_tabl(tabl, tmp, *j))
				{
					ft_strdel(&tmp);
					return (-1);
				}
				ft_strdel(&tmp);
			}
			else if (add_to_tabl(tabl, dir->d_name, *j))
				return (-1);
		}
	return (*j);
}

static int	fill_tabl_all_files(DIR **fd, char ***tabl, int *j, char *value)
{
	struct dirent	*dir;
	char			*tmp;
	char			*path;

	value = which_file(value, fd, &path);
	while (*fd && (dir = readdir(*fd)))
	{
		if (!(ft_strnequ(dir->d_name, ".", 1)))
		{
			*j += 1;
			if (check_directory(dir->d_name, path))
			{
				tmp = ft_strjoin(dir->d_name, "/");
				if (add_to_tabl(tabl, tmp, *j))
				{
					ft_strdel(&tmp);
					return (-1);
				}
				ft_strdel(&tmp);
			}
			else if (add_to_tabl(tabl, dir->d_name, *j))
				return (-1);
		}
	}
	return (*j);
}

char		**get_files(char *value, bool all, int *total)
{
	int				j;
	char			**tabl;
	DIR				*fd;

	j = 0;
	fd = NULL;
	if (!(tabl = (char**)malloc(sizeof(char*) * 2)))
		return (NULL);
	tabl[j] = NULL;
	if (!all)
		j = fill_tabl_files(&fd, &tabl, value, &j);
	else
		j = fill_tabl_all_files(&fd, &tabl, &j, value);
	if (fd != NULL)
		closedir(fd);
	if (j == -1 && (*total = 0))
		ft_arrdel(&tabl);
	*total = j;
	return (tabl);
}
