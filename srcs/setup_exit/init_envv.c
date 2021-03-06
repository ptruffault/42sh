/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_envv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptruffau <ptruffau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/04 12:38:45 by ptruffau          #+#    #+#             */
/*   Updated: 2019/04/24 16:46:55 by fstadelw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "shell42.h"

static char	*get_shell_path(char *path)
{
	char	buff[4097];
	char	*tmp;

	ft_memset(buff, '\0', 4096);
	if (*path == '/' || !(getcwd(buff, 4096)))
		return (ft_strdup(path));
	if (ft_str_startwith(path, "./"))
		return (ft_strjoin(buff, path + 1));
	if ((tmp = ft_strchr(path, '.')))
	{
		if (tmp[0] == '.' && tmp[1] == '.')
		{
			buff[ft_strlen(buff)] = '/';
			return (ft_strjoin(buff, tmp));
		}
		else
			return (ft_strjoin(buff, tmp + 1));
	}
	else if (ft_strchr(path, '/'))
		return (ft_strdup(ft_strchr(path, '/')));
	buff[ft_strlen(buff)] = '/';
	if (ft_strlen(path) < 1)
		return (ft_strjoin(buff, "42sh"));
	return (ft_strjoin(buff, path));
}

static void	ft_update_shelvl(t_shell *sh)
{
	t_envv	*shell_lvl;
	int		lvl;

	if ((shell_lvl = get_tenvv(sh->env, "SHLVL")))
		lvl = ft_atoi(shell_lvl->value);
	else
		lvl = 0;
	sh->env = ft_new_envv_int(sh->env, "SHLVL", lvl + 1, EXP);
}

static char	*ft_update_pwd(t_shell *sh)
{
	char buff[4097];
	char *pwd;

	if ((pwd = getcwd(buff, 4096)))
	{
		if (sh)
		{
			sh->env = ft_new_envv(sh->env, "PWD", pwd, EXP);
			return (get_tenvv_val(sh->env, "PWD"));
		}
		return (pwd);
	}
	return (NULL);
}

static void	ft_setup_environ(t_shell *sh, char *shell_fold)
{
	char		*rc_path;

	ft_update_shelvl(sh);
	sh->env = ft_new_envv(sh->env, "SHELL_FOLD", shell_fold, IN);
	if (isatty(0) && isatty(1)
		&& (rc_path = ft_strjoin(shell_fold, "/sys/.42shrc")))
	{
		exec_file(rc_path, sh);
		ft_strdel(&rc_path);
	}
}

int			init_env(t_shell *sh, char **argv, char **envv)
{
	char *shell_fold;
	char *shell_path;

	sh->env = ft_setenv(sh->env, envv, 0, EXP);
	ft_update_pwd(sh);
	ft_init_builtins_tab(sh);
	if ((shell_path = get_shell_path(*argv)))
	{
		sh->env = ft_new_envv(sh->env, "SHELL", shell_path, EXP);
		shell_fold = ft_get_prev_path(shell_path);
		retrieve_path(sh);
		init_intern(sh);
		ft_setup_environ(sh, shell_fold);
		ft_strdel(&shell_path);
		return (1);
	}
	return (0);
}
