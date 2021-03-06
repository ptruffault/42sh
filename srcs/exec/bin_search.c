/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bin_search.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptruffau <ptruffau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/08 13:22:32 by ptruffau          #+#    #+#             */
/*   Updated: 2019/04/24 16:53:58 by fstadelw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <sys/stat.h>
#include "shell42.h"

static char	*check_without_path(char *input)
{
	struct stat	inf;
	char		*bin_path;

	if (!(bin_path = ft_new_path(".", input)))
		return (NULL);
	if (lstat(bin_path, &inf) == -1)
		ft_strdel(&bin_path);
	else
		return (bin_path);
	return (NULL);
}

char		*absolute_path(char *input, t_envv *envv)
{
	char		*path;
	struct stat	inf;
	char		*pwd;

	path = NULL;
	if (lstat(input, &inf) == -1)
	{
		if ((pwd = get_tenvv_val(envv, "PWD"))
			&& !(path = ft_new_path(pwd, input)))
			return (NULL);
		if (lstat(path, &inf) != -1)
			return (path);
		ft_strdel(&path);
		return (NULL);
	}
	return (ft_strdup(input));
}

char		*search_in_envv(char *input, t_envv *envv, int i)
{
	char		*bin_path;
	char		**path;
	struct stat	inf;

	if (!(path = ft_strsplit(get_tenvv_val(envv, "PATH"), ':')) || !path[0])
		return (check_without_path(input));
	while (path[i])
	{
		if (!(bin_path = ft_new_path(path[i], input)))
		{
			ft_freestrarr(&path);
			return (NULL);
		}
		if (lstat(bin_path, &inf) == -1)
			ft_strdel(&bin_path);
		else
		{
			ft_freestrarr(&path);
			return (bin_path);
		}
		i++;
	}
	ft_freestrarr(&path);
	return (NULL);
}

char		*get_bin_path(char *input, t_envv *envv)
{
	if (!ft_isempty(input) && ft_check_ascii(input))
	{
		if (*input == '.' || ft_strchr(input, '/'))
			return (absolute_path(input, envv));
		return (search_in_envv(input, envv, 0));
	}
	return (NULL);
}
