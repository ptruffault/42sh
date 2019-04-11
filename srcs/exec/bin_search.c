/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bin_search.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptruffau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/08 13:22:32 by ptruffau          #+#    #+#             */
/*   Updated: 2019/03/26 17:21:55 by stdenis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell42.h"

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

char		*search_in_envv(char *input, t_envv *envv)
{
	char		*bin_path;
	char		**path;
	struct stat	inf;
	int			i;

	i = 0;
	if (!(path = ft_strsplit(get_tenvv_val(envv, "PATH"), ':')))
		return (NULL);
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
		if (ft_str_startwith(input, "./") || ft_strchr(input, '/'))
			return (absolute_path(input, envv));
		return (search_in_envv(input, envv));
	}
	return (NULL);
}
