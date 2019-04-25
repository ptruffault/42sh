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

int			ft_unsetenv(t_shell *sh, char **t)
{
	int i;

	i = 0;
	if (t[i] && t[i][0] == '-' && t[i][1] != '-')
	{
		error("unset : invalid option :", t[i]);
		ft_putendl_fd("usage: unset [name ...]", 2);
		return (2);
	}
	if (t[i] && t[i][0] == '-' && t[i][1] == '-')
		i++;
	if (!sh->env)
		return (0);
	while (t[i])
		sh->env = ft_del_envv(sh->env, t[i++]);
	return (0);
}

int			ft_unsetalias(t_shell *sh, char **t)
{
	int i;

	i = 0;
	while (t[i] && t[i][0] == '-' && t[i][1] != '-')
	{
		if (only_a(&t[i++][1]))
			sh->alias = ft_free_tenvv(sh->alias);
		else
		{
			error("unalias : invalid option :", t[i - 1]);
			ft_putendl_fd("unalias [-a] [name ...]", 2);
			return (2);
		}
	}
	if (t[i] && t[i][0] == '-' && t[i][1] == '-')
		i++;
	if (!sh->alias)
		return (0);
	while (t[i])
		sh->alias = ft_del_envv(sh->alias, t[i++]);
	return (0);
}
