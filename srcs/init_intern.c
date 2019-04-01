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

void	export_intern(t_shell *sh, const char *var)
{
	t_envv	*head;
	t_envv	*tmp;

	tmp = NULL;
	head = sh->intern;
	while (var && head)
	{
		if ((head->name) && ft_strequ(var, head->name))
		{
			if (tmp)
				tmp->next = head->next;
			else
				sh->intern = head->next;
			head->next = sh->env;
			sh->env = head;
			return ;
		}
		tmp = head;
		head = head->next;
	}
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
		if (get_tenvv_val(sh->intern, "PATH"))
			export_intern(sh, "PATH");
		else if ((path = ft_strnew(0)))
		{
			fd = open("/etc/paths", O_RDONLY);
			while (fd >= 0 && get_next_line(fd, &line) > 0)
			{
				path = ft_strjoin_fr(path, line);
				path = ft_stradd(&path, ":");
			}
			ft_close(fd);
			if (path)
				sh->env = ft_new_envv(sh->env, "PATH", path);
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
	sh->intern = ft_new_envv(sh->intern, "HISTSIZE", "500");
	sh->intern = ft_new_envv(sh->intern, "CDPATH", "");
	sh->intern = ft_new_envv(sh->intern, "FCEDIT", "vim");
	sh->intern = ft_new_envv(sh->intern, "PS1", PS1);
	if ((usr = getpwnam(getlogin())))
	{
		sh->intern = ft_new_envv_int(sh->intern, "EUID", usr->pw_uid);
		sh->intern = ft_new_envv_int(sh->intern, "GROUPS", usr->pw_gid);
		if ((hi_path = ft_strjoin(usr->pw_dir, "/.42history"))
			&& (sh->intern = ft_new_envv(sh->intern, "HISTFILE", hi_path)))
		{
			sh->hist = init_hist(hi_path);
			ft_strdel(&hi_path);
		}
	}
	if ((hostname = ft_strnew(255)))
		if (!(gethostname(hostname, 254)))
			sh->intern = ft_new_envv(sh->intern, "HOSTNAME", hostname);
	ft_strdel(&hostname);
	return (0);
}
