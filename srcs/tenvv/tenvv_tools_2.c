/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tenvv_tools_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptruffau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/04 14:11:52 by ptruffau          #+#    #+#             */
/*   Updated: 2019/03/26 16:47:28 by stdenis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tenvv.h"

t_envv		*ft_tenvv_cpy(t_envv *src, bool exp)
{
	t_envv *tmp;
	t_envv *ret;

	if (!(ret = new_tenvv(exp)))
		return (NULL);
	tmp = ret;
	while (src)
	{
		while (src && !(src->exported == exp))
			src = src->next;
		if (!src)
			return (ret);
		if (!(tmp->name = ft_strdup(src->name))
			|| (src->value && !(tmp->value = ft_strdup(src->value))))
			return (ft_free_tenvv(ret));
		src = src->next;
		while (src && !(src->exported == exp))
			src = src->next;
		if (src)
		{
			tmp->next = new_tenvv(exp);
			tmp = tmp->next;
		}
	}
	return (ret);
}

t_envv		*ft_push_tenvv(t_envv *dest, const t_envv *src)
{
	while (src)
	{
		dest = ft_new_envv(dest, src->name, src->value, TRUE);
		src = src->next;
	}
	return (dest);
}

static void	ft_shitty_norme(t_envv **prev, t_envv **tmp)
{
	t_envv *t;

	t = *tmp;
	*prev = t;
	*tmp = t->next;
}

t_envv		*ft_pull_tenvv(t_envv *dest, const t_envv *src)
{
	t_envv	*tmp;
	t_envv	*prev;
	t_envv	*save;

	while (src && src->name)
	{
		tmp = dest;
		prev = NULL;
		while (tmp)
		{
			if (ft_strequ(tmp->name, src->name))
			{
				save = tmp->next;
				del_tenvv(tmp);
				if (prev)
					prev->next = save;
				else
					dest = save;
				break ;
			}
			ft_shitty_norme(&prev, &tmp);
		}
		src = src->next;
	}
	return (dest);
}
