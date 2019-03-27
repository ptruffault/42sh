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

t_envv	*ft_tenvv_cpy(t_envv *src)
{
	t_envv *tmp;
	t_envv *ret;

	if (!(ret = new_tenvv()))
		return (NULL);
	tmp = ret;
	while (src)
	{
		if (!(tmp->name = ft_strdup(src->name))
		|| (src->value && !(tmp->value = ft_strdup(src->value))))
			return (ft_free_tenvv(ret));
		src = src->next;
		if (src)
		{
			tmp->next = new_tenvv();
			tmp = tmp->next;
		}
	}
	return (ret);
}

t_envv	*del_tenvv(t_envv *envv)
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

t_envv	*ft_free_tenvv(t_envv *envv)
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

t_envv	*ft_push_tenvv(t_envv *dest, const t_envv *src)
{
	while (src)
	{
		dest = ft_new_envv(dest, src->name, src->value);
		src = src->next;
	}
	return (dest);
}

t_envv *ft_pull_tenvv(t_envv *dest, const t_envv *src)
 {
 	t_envv *tmp;
 	t_envv *prev;
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
 			prev = tmp;
 			tmp = tmp->next;
 		}
 		src = src->next;
 	}
 	return (dest);
 }
