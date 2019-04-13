/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_intern.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stdenis <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/04 12:38:45 by stdenis           #+#    #+#             */
/*   Updated: 2019/03/26 17:21:55 by stdenis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell42.h"
#include "get_input.h"

static void	ft_intern_var(t_shell *sh)
{
	sh->env = ft_new_envv(sh->env, "HISTSIZE", "500", IN);
	sh->env = ft_new_envv(sh->env, "!", "0", IN);
	sh->env = ft_new_envv(sh->env, "?", "0", IN);
	sh->env = ft_new_envv_int(sh->env, "$", (int)sh->pid, IN);
	sh->env = ft_new_envv(sh->env, "CDPATH", "", IN);
	sh->env = ft_new_envv(sh->env, "FCEDIT", "vim", IN);
	sh->env = ft_new_envv(sh->env, "PS1", PS1, IN);
	sh->env = ft_new_envv(sh->env, "PS2", PS2, IN);
}

void		ft_init_builtins_tab(t_shell *sh)
{
	sh->builtins[0] = "exit";
	sh->builtins[1] = "cd";
	sh->builtins[2] = "export";
	sh->builtins[3] = "unset";
	sh->builtins[4] = "alias";
	sh->builtins[5] = "unalias";
	sh->builtins[6] = "echo";
	sh->builtins[7] = "set";
	sh->builtins[8] = "type";
	sh->builtins[9] = "jobs";
	sh->builtins[10] = "hi";
	sh->builtins[11] = "fg";
	sh->builtins[12] = "bg";
	sh->builtins[13] = "fc";
	sh->builtins[14] = "hash";
	sh->builtins[15] = "test";
	sh->builtins[16] = NULL;
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

void		retrieve_path(t_shell *sh)
{
	char	*line;
	char	*path;
	int		fd;

	line = NULL;
	path = NULL;
	if (!(get_tenvv_val(sh->env, "PATH")))
	{
		if ((path = ft_strnew(0)))
		{
			fd = open("/etc/paths", O_RDONLY);
			while (fd >= 0 && get_next_line(fd, &line) > 0)
			{
				path = ft_strjoin_fr(path, line);
				path = ft_stradd(&path, ":");
			}
			ft_close(fd);
			if (path)
				sh->env = ft_new_envv(sh->env, "PATH", path, EXP);
			ft_strdel(&path);
		}
	}
}

int			init_intern(t_shell *sh)
{
	struct passwd	*usr;
	char			*hi_path;
	char			*hostname;

	hostname = NULL;
	ft_intern_var(sh);
	if (isatty(0) && (usr = getpwnam(getlogin())))
	{
		sh->env = ft_new_envv_int(sh->env, "EUID", usr->pw_uid, IN);
		sh->env = ft_new_envv_int(sh->env, "GROUPS", usr->pw_gid, IN);
		if ((hi_path = ft_strjoin(usr->pw_dir, "/.42history"))
			&& (sh->env = ft_new_envv(sh->env, "HISTFILE", hi_path, IN)))
		{
			sh->hist = init_hist(hi_path);
			ft_strdel(&hi_path);
		}
	}
	if (isatty(0) && (hostname = ft_strnew(255)))
		if (!(gethostname(hostname, 254)))
			sh->env = ft_new_envv(sh->env, "HOSTNAME", hostname, IN);
	ft_strdel(&hostname);
	return (0);
}
