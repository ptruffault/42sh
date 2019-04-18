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

static int		change_dir(char *path, t_shell *sh, t_opts opts)
{
	char	buff[4097];
	char	*cwd;

	if (!chdir(path))
	{
		cwd = ft_strdup_path(path);
		if (opts & 0x04)
			ft_printf("%s\n", cwd);
		sh->env = ft_new_envv(sh->env, "OLDPWD",
			get_tenvv_val(sh->env, "PWD"), EXP);
		if ((opts & 0x02))
			sh->env = ft_new_envv(sh->env, "PWD", getcwd(buff, 4096), EXP);
		else
			sh->env = ft_new_envv(sh->env, "PWD", cwd, EXP);
		ft_strdel(&cwd);
		return (0);
	}
	if (access(path, F_OK) == -1)
		error("no such file or directory: ", path);
	else if (access(path, R_OK) == -1)
		error("permission denied: ", path);
	else
		error("not a directory: ", path);
	return (1);
}

static int		get_path_cd(char *path, t_shell *sh, t_opts opts)
{
	char	*curpath;
	bool	pwd_f;
	int		ret;

	curpath = NULL;
	pwd_f = false;
	if ((opts & 0x02) && (path[0] == '/' || path[0] == '.'))
		return (change_dir(path, sh, opts));
	curpath = trans_cdpath(path, sh, &pwd_f, &opts);
	while (curpath && (ft_strstr(curpath, "..") || ft_strstr(curpath, "//")
			|| ft_strstr(curpath, "./") || ft_strstr(curpath, "/.")))
		trim_path(curpath);
	if (ft_strlen(curpath) == 0)
		ft_strcpy(curpath, "/");
	if (ft_strlen(curpath) > PATH_MAX)
		ret = change_dir(path, sh, (opts | 0x02));
	else
		ret = change_dir(curpath, sh, opts);
	if (pwd_f)
		ft_strdel(&curpath);
	return (ret);
}

static t_opts	get_options_cd(char **input, size_t *tabl)
{
	t_opts			opts;
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

int				ft_cd(char **input, t_shell *sh)
{
	char			*val;
	t_opts			opts;
	size_t			tabl;

	tabl = 1;
	opts = get_options_cd(input, &tabl);
	if (opts & 0x10)
		error("cd: invalid option", input[tabl - 1]);
	else if (!(input[1]))
	{
		if ((val = get_tenvv_val(sh->env, "HOME")))
			return (get_path_cd(val, sh, opts));
		else
			error("UNSET VAR", "HOME");
	}
	else if (input[1][0] == '-' && input[1][1] == '\0')
	{
		if ((val = get_tenvv_val(sh->env, "OLDPWD")))
			return (get_path_cd(val, sh, (opts | 0x04)));
		else
			error("UNSET VAR", "OLDPWD");
	}
	else if (input[tabl])
		return (get_path_cd(input[tabl], sh, opts));
	return (1);
}
