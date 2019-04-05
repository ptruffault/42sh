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

char	*trim_path(char *path)
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

void	retrieve_path(t_shell *sh)
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
				sh->env = ft_new_envv(sh->env, "PATH", path, true);
			ft_strdel(&path);
		}
	}
}

int		init_intern(t_shell *sh)
{
	struct passwd	*usr;
	char			*hi_path;
	char			*hostname;

	hostname = NULL;
	sh->env = ft_new_envv(sh->env, "HISTSIZE", "500", false);
	sh->env = ft_new_envv(sh->env, "!", "0", false);
	sh->env = ft_new_envv(sh->env, "?", "0", false);
	sh->env = ft_new_envv_int(sh->env, "$", sh->pid, false);
	sh->env = ft_new_envv(sh->env, "CDPATH", "", false);
	sh->env = ft_new_envv(sh->env, "FCEDIT", "vim", false);
	sh->env = ft_new_envv(sh->env, "PS1", PS1, false);
	sh->env = ft_new_envv(sh->env, "PS2", PS2, false);
	if ((usr = getpwnam(getlogin())))
	{
		sh->env = ft_new_envv_int(sh->env, "EUID", usr->pw_uid, false);
		sh->env = ft_new_envv_int(sh->env, "GROUPS", usr->pw_gid, false);
		if ((hi_path = ft_strjoin(usr->pw_dir, "/.42history"))
			&& (sh->env = ft_new_envv(sh->env, "HISTFILE", hi_path, false)))
		{
			sh->hist = init_hist(hi_path);
			ft_strdel(&hi_path);
		}
	}
	if ((hostname = ft_strnew(255)))
		if (!(gethostname(hostname, 254)))
			sh->env = ft_new_envv(sh->env, "HOSTNAME", hostname, false);
	ft_strdel(&hostname);
	return (0);
}
