/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unsetenv.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adi-rosa <adi-rosa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/05 13:35:56 by adi-rosa          #+#    #+#             */
/*   Updated: 2019/04/24 17:11:33 by fstadelw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "shell42.h"
#include "tenvv.h"

t_envv		*del_tenvv(t_envv *envv)
{
	if (envv)
	{
		ft_strdel(&envv->name);
		ft_strdel(&envv->value);
		envv->next = NULL;
		free(envv);
	}
	return (NULL);
}

t_envv		*ft_free_tenvv(t_envv *envv)
{
	t_envv *tmp;

	while (envv)
	{
		tmp = envv;
		envv = envv->next;
		tmp = del_tenvv(tmp);
	}
	return (NULL);
}

t_envv		*ft_del_envv(t_envv *envv, char *name)
{
	t_envv *tmp;
	t_envv *prev;

	tmp = envv->next;
	prev = envv;
	if (ft_strequ(envv->name, name))
	{
		tmp = envv->next;
		envv = del_tenvv(envv);
		return (tmp);
	}
	while (tmp)
	{
		if (ft_strequ(tmp->name, name))
		{
			prev->next = tmp->next;
			tmp = del_tenvv(tmp);
			return (envv);
		}
		prev = tmp;
		tmp = tmp->next;
	}
	return (envv);
}

static int	only_a(char *str)
{
	int		i;

	i = -1;
	while (str[++i])
		if (str[i] != 'a')
			return (0);
	return (1);
}

t_envv		*ft_unsetenv(t_envv *envv, char **t)
{
	int i;

	i = 0;
	if (!envv)
		return (NULL);
	while (t[i] && t[i][0] == '-' && only_a(&t[i][1]))
		i++;
	if (!only_a(&t[i][1]))
	{
		error("unset or unalias : invalid option :", t[i]);
		ft_putendl_fd("usage: unset [name ...] or unalias [-a] [name ...]", 2);
		ft_get_set_shell(NULL)->env = ft_new_envv_int(ft_get_set_shell(NULL)->env, "?", 1, IN);
		return (envv);
	}
	if (i > 0)
		return (ft_free_tenvv(envv));
	while (t[i])
		envv = ft_del_envv(envv, t[i++]);
	return (envv);
}
