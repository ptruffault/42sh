/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hash.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stdenis <stdenis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/15 13:38:24 by stdenis           #+#    #+#             */
/*   Updated: 2019/03/17 18:34:45 by stdenis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell42.h"

static int		print_htable(t_shell *sh)
{
	int			i;
	t_hash		*value;
	bool		first;

	i = -1;
	first = false;
	while (++i < HASHTABLE_SIZE)
	{
		if ((value = sh->htable[i]))
		{
			while (value != NULL)
			{
				if (!first)
					ft_printf("%4s    %s\n", "hits", "command");
				ft_printf("%4d    %s\n", value->hit, value->path);
				value = value->next;
				first = true;
			}
		}
	}
	if (!first)
		ft_printf("hash: hash table empty\n");
	return (0);
}

t_hash			*search_in_htable(const char *str, t_shell *sh)
{
	unsigned int	hash;
	t_hash			*value;

	if (str == NULL)
		return (NULL);
	hash = ft_hash(str);
	if (!(value = sh->htable[hash]))
		return (NULL);
	while (value != NULL && ft_strequ(value->command, str) != 1)
		value = value->next;
	return (value);
}

int				add_in_htable(const char *str, const char *path, t_shell *sh)
{
	unsigned int	hash;
	t_hash			*value;

	if (path == NULL || str == NULL)
		return (1);
	hash = ft_hash(str);
	if (!(value = (t_hash*)malloc(sizeof(t_hash))))
		return (1);
	if (!(value->command = ft_strdup(str)))
	{
		free(value);
		return (1);
	}
	ft_strcpy(value->path, path);
	value->hit = 0;
	if (sh->htable[hash] != NULL)
		value->next = sh->htable[hash];
	else
		value->next = NULL;
	sh->htable[hash] = value;
	return (0);
}

int				cleaning_htable(char *cmd, t_shell *sh)
{
	int			i;
	t_hash		*value;
	t_hash		*next;

	i = -1;
	if (cmd != NULL && !(ft_strequ(cmd, "-r")))
	{
		error("hash: bad option :", &cmd[1]);
		return (1);
	}
	while (++i < HASHTABLE_SIZE)
	{
		value = sh->htable[i];
		while (value != NULL)
		{
			next = value->next;
			if (value->command != NULL)
				ft_strdel(&value->command);
			free(value);
			value = next;
		}
		sh->htable[i] = NULL;
	}
	return (0);
}

int				builtin_htable(char **cmd, t_shell *sh)
{
	char			*path;
	t_hash			*value;

	value = NULL;
	if (!*cmd)
		return (print_htable(sh));
	else if (ft_str_startwith(*cmd, "-"))
		return (cleaning_htable(*cmd, sh));
	while (*cmd)
	{
		if (!(path = get_bin_path(*cmd, sh->env)))
			error("hash: no such command:", *cmd);
		else
		{
			if (!(value = search_in_htable(*cmd, sh)))
				add_in_htable(*cmd, path, sh);
			ft_strdel(&path);
		}
		++cmd;
	}
	return (0);
}