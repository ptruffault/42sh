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

static char	*concat_pwd(t_shell *sh, char *path, bool *pwd_f)
{
	char		*pwd;
	char		buff[4097];

	if (!(pwd = get_tenvv_val(sh->env, "PWD")))
		pwd = getcwd(buff, 4096);
	if (!(pwd = ft_strdup(pwd)))
		return (path);
	if (pwd[ft_strlen(pwd) - 1] != '/')
		pwd = ft_stradd(&pwd, "/");
	pwd = ft_stradd(&pwd, path);
	*pwd_f = true;
	return (pwd);
}

char		*ft_strdup_path(char *src)
{
	size_t	l;
	size_t	i;
	char	*res;

	i = 0;
	l = ft_strlen((char*)src);
	if (l > 2 && src[l - 1] == '/')
	{
		src[l - 1] = '\0';
		l -= 1;
	}
	if (!(res = (char *)malloc(sizeof(char) * (l + 1))))
		return (0);
	while (src[i] != '\0')
	{
		res[i] = src[i];
		i++;
	}
	res[i] = '\0';
	return (res);
}

char		*trim_path(char *path)
{
	int		i;
	int		save;

	i = -1;
	save = 0;
	while (path[++i] != '\0')
	{
		if (path[i] == '.' && path[i + 1] == '\0')
			path[i] = '\0';
		if (path[i] == '.' && path[i + 1] == '.')
			if (save >= 0)
				return (ft_strcpy(path + save, path + i + 2));
		if (path[i] == '.' && path[i + 1] == '/')
			if (save >= 0)
				return (ft_strcpy(path + i, path + i + 1));
		if (path[i] == '/' && path[i + 1] == '/')
			return (ft_strcpy(path + i, path + i + 1));
		if (path[i] == '/' && path[i + 1] != '.')
			save = i;
	}
	return (path);
}

char		*trans_cdpath(char *path, t_shell *sh, bool *pwd_f, t_opts *opts)
{
	char	*cdpath;
	char	*curpath;

	curpath = NULL;
	if ((cdpath = get_tenvv_val(sh->env, "CDPATH")) && ft_strlen(cdpath) > 0)
		curpath = try_cdpath(cdpath, path, pwd_f, opts);
	if (!curpath && path[0] != '/')
		curpath = concat_pwd(sh, path, pwd_f);
	else if (!curpath)
		curpath = path;
	return (curpath);
}

char		*try_cdpath(char *cdpath, char *path, bool *pwd_f, t_opts *opts)
{
	char		**tpath;
	char		*res;
	struct stat	dir;
	int			i;

	i = -1;
	if (path[0] != '/' && path[0] != '.' && (tpath = ft_strsplit(cdpath, ':')))
	{
		while (tpath[++i] != 0)
		{
			tpath[i] = ft_stradd(&tpath[i], "/");
			tpath[i] = ft_stradd(&tpath[i], path);
			if (tpath[i] && !(stat(tpath[i], &dir)) && S_ISDIR(dir.st_mode))
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
