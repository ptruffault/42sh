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

int			fill_tabl_binary(int *j, char ***tabl, char *value, char *path)
{
	DIR				*fd;
	struct dirent	*dir;

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
				if (add_to_tabl(tabl, dir->d_name, *j) && !closedir(fd))
					return (-1);
			}
		}
	}
	if (fd)
		closedir(fd);
	return (*j);
}

int			fill_tabl_all_bin(int *j, char ***tabl, char *path)
{
	DIR				*fd;
	struct dirent	*dir;

	fd = opendir(path);
	while (fd && (dir = readdir(fd)))
	{
		if (!(ft_strequ(dir->d_name, "."))
			&& !(ft_strequ(dir->d_name, "..")))
		{
			if (check_exec(dir->d_name, path) && !check_builtin(dir->d_name))
			{
				*j += 1;
				if (add_to_tabl(tabl, dir->d_name, *j) && !closedir(fd))
					return (-1);
			}
		}
	}
	if (fd)
		closedir(fd);
	return (*j);
}

int			fill_tabl_builtin(char ***tabl, char *value, bool all, int *j)
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
	if (!(path = ft_strsplit(get_tenvv_val(sh->env, "PATH"), ':')))
		return (NULL);
	set_null_tabl(tabl, 2);
	while (path[++i])
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
