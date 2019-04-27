/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tenvv_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptruffau <ptruffau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/04 14:11:41 by ptruffau          #+#    #+#             */
/*   Updated: 2019/04/27 18:54:07 by fstadelw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "shell42.h"
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

int		only_a(char *str)
{
	int		i;

	i = -1;
	while (str[++i])
		if (str[i] != 'a')
			return (0);
	return (1);
}

int		ft_puttenvv(t_envv *t, short status, int mode)
{
	int i;

	i = -1;
	while (t && t->name)
	{
		if ((t->status & status))
		{
			i = 0;
			if (mode == 0 && isatty(1))
				ft_printf(VERT"%s\033[00m=%s\n", t->name, t->value);
			else if (mode == 0)
				ft_printf("%s=%s\n", t->name, t->value);
			else if (mode == 1)
				print_for_export(t);
			else if (mode == 2)
				print_for_export_p(t);
			else if (mode == 3)
				print_for_alias(t);
		}
		t = t->next;
	}
	return (i);
}
