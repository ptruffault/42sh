/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tenvv_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptruffau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/04 14:11:41 by ptruffau          #+#    #+#             */
/*   Updated: 2018/07/04 14:11:42 by ptruffau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <tenvv.h>

t_envv	*new_tenvv(void)
{
	t_envv *new;

	if (!(new = (t_envv *)malloc(sizeof(t_envv))))
		return (NULL);
	new->next = NULL;
	new->name = NULL;
	new->value = NULL;
	return (new);
}

t_envv	*get_tenvv(t_envv *envv, char *name)
{
	while (name && envv)
	{
		if ((envv->name) && ft_strequ(name, envv->name))
			return (envv);
		envv = envv->next;
	}
	return (NULL);
}

char	*get_tenvv_val(const t_envv *envv, char *name)
{
	t_envv *tmp;

	if ((tmp = get_tenvv((t_envv *)envv, name)))
		return (tmp->value);
	return (NULL);
}

int	ft_puttenvv(const t_envv *t)
{
	int i = -1;

	while (t && t->name)
	{
		i = 0;
		ft_printf("\033[1;32m\033[04m%s\033[00m = %s\n", t->name, t->value);
		t = t->next;
	}
	return (i);
}

t_envv	*ft_changetenvv_val(t_envv *envv, char *name, char *new_val)
{
	t_envv *tmp;

	if ((tmp = get_tenvv(envv, name)))
	{
		ft_strdel(&tmp->value);
		tmp->value = ft_strdup(new_val);
	}
	return (envv);
}
