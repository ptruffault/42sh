/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   binary_completion.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stdenis <stdenis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/18 15:33:46 by stdenis           #+#    #+#             */
/*   Updated: 2019/04/24 17:08:11 by fstadelw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <dirent.h>
#include <stdlib.h>
#include "shell42.h"

static int	fill_tabl_binary(int *j, char ***tabl, char *value, char *path)
{
	DIR				*fd;
	struct dirent	*dir;
	int				ret;

	fd = opendir(path);
	while (fd && (dir = readdir(fd)))
	{
		if (!(ft_strequ(dir->d_name, "."))
			&& !(ft_strequ(dir->d_name, "..")))
		{
			if ((ft_str_startwith(dir->d_name, value))
				&& check_exec(dir->d_name, path) && !check_builtin(dir->d_name))
			{
				*j += 1;
				if ((ret = add_to_tabl(tabl, dir->d_name, *j)) == 1)
					return (closedir(fd) - 1);
			}
		}
	}
	if (fd)
		closedir(fd);
	return (*j);
}

static int	fill_tabl_all_bin(int *j, char ***tabl, char *path)
{
	DIR				*fd;
	struct dirent	*dir;
	int				ret;

	fd = opendir(path);
	ret = 0;
	while (fd && (dir = readdir(fd)))
	{
		if (!(ft_strequ(dir->d_name, "."))
			&& !(ft_strequ(dir->d_name, "..")))
		{
			if (check_exec(dir->d_name, path) && !check_builtin(dir->d_name))
			{
				*j += 1;
				if ((ret = add_to_tabl(tabl, dir->d_name, *j)) == 1)
					return (closedir(fd) - 1);
			}
		}
	}
	if (fd)
		closedir(fd);
	return (*j);
}

static int	fill_tabl_builtin(char ***tabl, char *value, bool all, int *j)
{
	int			i;
	t_shell		*sh;

	i = -1;
	sh = ft_get_set_shell(NULL);
	while (sh->builtins[++i])
	{
		if (!all && ft_str_startwith(sh->builtins[i], value))
		{
			*j += 1;
			if (add_to_tabl(tabl, sh->builtins[i], *j))
				return (-1);
		}
		else if (all)
		{
			*j += 1;
			if (add_to_tabl(tabl, sh->builtins[i], *j))
				return (-1);
		}
	}
	return (*j);
}

char		**get_binary(t_shell *sh, char *value, bool all, int *total)
{
	int				i;
	int				j;
	char			**tabl;
	char			**path;

	i = -1;
	j = 0;
	if (!(tabl = (char**)malloc(sizeof(char*) * 2)))
		return (NULL);
	set_null_tabl(tabl, 2);
	if (!(path = ft_strsplit(get_tenvv_val(sh->env, "PATH"), ':')))
		return (tabl);
	while (path[++i] && tabl && j != -1)
	{
		if (!all)
			j = fill_tabl_binary(&j, &tabl, value, path[i]);
		else
			j = fill_tabl_all_bin(&j, &tabl, path[i]);
	}
	if (j == -1 || (fill_tabl_builtin(&tabl, value, all, &j)) == -1)
		ft_arrdel(&tabl);
	*total = j;
	ft_arrdel(&path);
	return (tabl);
}
