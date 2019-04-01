/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptruffau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/04 14:10:52 by ptruffau          #+#    #+#             */
/*   Updated: 2019/03/26 17:21:55 by stdenis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell42.h"

t_envv				*change_dir(char *path, t_envv *envv, unsigned int opts)
{
	char	buff[4097];
	char	*cwd;

	cwd = NULL;
	if (!chdir(path))
	{
		cwd = ft_strdup(path);
		if (ft_strequ(cwd, get_tenvv_val(envv, "OLDPWD")))
			ft_printf("%s\n", cwd);
		envv = ft_new_envv(envv, "OLDPWD", get_tenvv_val(envv, "PWD"), true);
		if ((opts & 0x02))
			envv = ft_new_envv(envv, "PWD", getcwd(buff, 4096), true);
		else
			envv = ft_new_envv(envv, "PWD", cwd, true);
		ft_strdel(&cwd);
	}
	else
	{
		if (access(path, F_OK) == -1)
			error("no such file or directory: ", path);
		else if (access(path, R_OK) == -1)
			error("permission denied: ", path);
		else
			error("not a directory: ", path);
	}
	return (envv);
}

char				*concat_pwd(t_envv *envv, char *path, bool *pwd_f)
{
	char		*pwd;
	char		buff[4097];

	if (!(pwd = get_tenvv_val(envv, "PWD")))
		pwd = getcwd(buff, 4096);
	if (!(pwd = ft_strdup(pwd)))
		return (path);
	pwd = ft_stradd(&pwd, "/");
	pwd = ft_stradd(&pwd, path);
	*pwd_f = true;
	return (pwd);
}

t_envv				*get_path_cd(char *path, t_envv *envv, unsigned int opts)
{
	char	*curpath;
	bool	pwd_f;
	char	*cdpath;

	pwd_f = false;
	curpath = NULL;
	if ((opts & 0x02) && (path[0] == '/' || path[0] == '.'))
		return (change_dir(path, envv, opts));
	if ((cdpath = get_tenvv_val(envv, "CDPATH")) && ft_strlen(cdpath) > 0)
		curpath = try_cdpath(cdpath, path, &pwd_f);
	if (!curpath && path[0] != '/')
		curpath = concat_pwd(envv, path, &pwd_f);
	else if (!curpath)
		curpath = path;
	while (ft_strstr(curpath, "..") || ft_strstr(curpath, "//"))
		trim_path(curpath);
	if (ft_strlen(curpath) == 0)
		ft_strcpy(curpath, "/");
	if (ft_strlen(curpath) > PATH_MAX)
		envv = change_dir(path, envv, (opts | 0x02));
	else
		envv = change_dir(curpath, envv, opts);
	if (pwd_f)
		ft_strdel(&curpath);
	return (envv);
}

static unsigned int	get_options_cd(char **input, size_t *tabl)
{
	unsigned int	opts;
	size_t			i;
	size_t			j;

	i = 0;
	opts = 0;
	while (input[++i] && input[i][0] == '-' && input[i][1] != '\0')
	{
		j = 0;
		while (input[i][++j] != '\0')
		{
			if (input[i][j] == 'L')
				opts = (opts | 0x01) & ~(0x02);
			else if (input[i][j] == 'P')
				opts = (opts | 0x02) & ~(0x01);
			else
				opts = (opts | 0x10) & ~(0x01) & ~(0x02);
		}
	}
	*tabl = i;
	return (opts);
}

t_envv				*ft_cd(char **input, t_envv *envv)
{
	char			*val;
	unsigned int	opts;
	size_t			tabl;

	val = NULL;
	tabl = 1;
	opts = get_options_cd(input, &tabl);
	if (opts & 0x10)
		error("cd: invalid option", input[tabl - 1]);
	else if (!(input[1]))
	{
		if ((val = get_tenvv_val(envv, "HOME")))
			return (get_path_cd(val, envv, opts));
		else
			error("UNSET VAR", "HOME");
	}
	else if (input[1][0] == '-' && input[1][1] == '\0')
	{
		if ((val = get_tenvv_val(envv, "OLDPWD")))
			return (get_path_cd(val, envv, opts));
		else
			error("UNSET VAR", "OLDPWD");
	}
	else if (input[tabl])
		return (get_path_cd(input[tabl], envv, opts));
	return (envv);
}
