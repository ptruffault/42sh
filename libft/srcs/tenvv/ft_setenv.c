/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adi-rosa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/05 13:41:36 by adi-rosa          #+#    #+#             */
/*   Updated: 2019/02/05 13:45:06 by adi-rosa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <tenvv.h>

t_envv	*ft_new_envv(t_envv *envv, char *name, char *value)
{
	t_envv	*ret;
	t_envv	*tmp;

	if ((tmp = get_tenvv(envv, name)))
		return (ft_changetenvv_val(envv, name, value));
	if (!name || !(ret = new_tenvv()))
		return (envv);
	if (!(ret->name = ft_strdup(name)) || !(ret->value = ft_strdup(value)))
	{
		del_tenvv(ret);
		return (envv);
	}
	ret->next = envv;
	return (ret);
}

t_envv	*ft_setenv(t_envv *envv, char **t)
{
	char	*name;
	char	*val;
	int		i;

	i = 0;
	while (t[i])
	{
		if (ft_isequal(t[i]))
		{
			name = get_name(t[i]);
			val = get_value(t[i]);
			envv = ft_new_envv(envv, name, val);
			ft_strdel(&name);
			ft_strdel(&val);
		}
		else if (t[i + 1])
		{
			envv = ft_new_envv(envv, t[i], t[i + 1]);
			i++;
		}
		else
			warning("uninitialised value", t[i]);
		i++;
	}
	return (envv);
}
