/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cdpath.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stdenis <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/04 14:10:52 by stdenis           #+#    #+#             */
/*   Updated: 2019/03/26 17:21:55 by stdenis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell42.h"

char		*try_cdpath(char *cdpath, char *path, bool *pwd_f, unsigned int *opts)
{
	char		**tpath;
	char		*res;
	struct stat	dir;
	int		i;

	i = -1;
	if (path[0] != '/' && path[0] != '.' && (tpath = ft_strsplit(cdpath, ':')))
	{
		while (tpath[++i] != 0)
		{
			tpath[i] = ft_stradd(&tpath[i], "/");
			tpath[i] = ft_stradd(&tpath[i], path);
			if (!(lstat(tpath[i], &dir)))
				if (S_ISDIR(dir.st_mode))
				{
					res = ft_strdup(tpath[i]);
					ft_freestrarr(&tpath);
					*opts = (*opts | 0x04);
					*pwd_f = true;
					return (res);
				}
		}
		ft_freestrarr(&tpath);
	}
	return (NULL);
}
