/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tenvv_tools_tmp.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptruffau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/04 14:11:52 by ptruffau          #+#    #+#             */
/*   Updated: 2019/03/26 16:47:28 by stdenis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tenvv.h"
#include "shell42.h"

t_envv		*ft_save_tenvv(t_envv *envv, t_envv *tmp)
{
	t_envv	*save;
	t_envv	*org;

	org = envv;
	save = NULL;
	while (tmp && tmp->name)
	{
		while (org)
		{
			if (tmp->name && ft_strequ(tmp->name, org->name))
				save = ft_new_envv(save, org->name, org->value, org->status);
			org = org->next;
		}
		tmp = tmp->next;
	}
	return (save);
}

t_envv		*ft_push_tenvv(t_envv *dest, const t_envv *src, short status)
{
	while (src)
	{
		dest = ft_new_envv(dest, src->name, src->value, status);
		if (dest && status > 0)
			dest->status = status;
		else if (dest)
			dest->status = src->status;
		src = src->next;
	}
	return (dest);
}

t_envv		*ft_remove_tmp(t_envv *src)
{
	t_envv	*next;
	t_envv	*dest;
	t_envv	*prev;

	prev = NULL;
	dest = src;
	while (dest)
	{
		if (dest->status & TMP)
		{
			next = dest->next;
			del_tenvv(dest);
			dest = next;
			if (prev)
				prev->next = dest;
			else
				src = dest;
		}
		else
		{
			prev = dest;
			dest = dest->next;
		}
	}
	return (src);
}
