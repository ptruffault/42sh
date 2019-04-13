/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tenvv_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptruffau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/04 14:11:41 by ptruffau          #+#    #+#             */
/*   Updated: 2019/03/26 16:47:28 by stdenis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tenvv.h"
#include "ft_printf.h"

t_envv	*new_tenvv(short status)
{
	t_envv *node;

	if (!(node = (t_envv *)malloc(sizeof(t_envv))))
		return (NULL);
	node->next = NULL;
	node->status = status;
	node->name = NULL;
	node->value = NULL;
	return (node);
}

t_envv	*get_tenvv(t_envv *envv, const char *name)
{
	while (name && envv)
	{
		if ((envv->name) && ft_strequ(name, envv->name))
			return (envv);
		envv = envv->next;
	}
	return (NULL);
}

char	*get_tenvv_val(t_envv *envv, const char *name)
{
	t_envv *tmp;

	if ((tmp = get_tenvv((t_envv *)envv, name)))
		return (tmp->value);
	return (NULL);
}

int		ft_puttenvv(t_envv *t, short status)
{
	int i;

	i = -1;
	while (t && t->name)
	{
		if (t->status == status)
		{
			i = 0;
			ft_printf("\033[1;32m\033[04m%s\033[00m = %s\n", t->name, t->value);
		}
		t = t->next;
	}
	return (i);
}

t_envv	*ft_changetenvv_val(t_envv *envv, const char *name, const char *new_val)
{
	t_envv *tmp;

	if ((tmp = get_tenvv(envv, name)))
	{
		ft_strdel(&tmp->value);
		tmp->value = ft_strdup(new_val);
	}
	return (envv);
}
