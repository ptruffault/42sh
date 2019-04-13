/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adi-rosa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/05 13:41:36 by adi-rosa          #+#    #+#             */
/*   Updated: 2019/03/26 16:47:28 by stdenis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell42.h"
#include "tenvv.h"

char	*ft_split_equal(char *str, char **aft)
{
	size_t	i;

	i = 0;
	while (str[i] != '\0' && str[i] != '=')
		i++;
	if (str[i] == '\0')
	{
		*aft = NULL;
		return (str);
	}
	str[i] = '\0';
	*aft = &str[i + 1];
	return (str);
}

t_envv	*ft_new_envv_int(t_envv *envv, const char *name, int val, short status)
{
	t_envv	*ret;
	t_envv	*tmp;
	char	*value;

	value = ft_itoa(val);
	if (envv && name && (tmp = get_tenvv(envv, name)))
	{
		ft_strdel(&tmp->value);
		tmp->value = value;
		return (envv);
	}
	if (!name || !value || !(ret = new_tenvv(status)))
		return (envv);
	if (!(ret->name = ft_strdup(name)))
	{
		del_tenvv(ret);
		return (envv);
	}
	ret->value = value;
	ret->next = envv;
	return (ret);
}

t_envv	*ft_new_envv(t_envv *envv, const char *name, const char *val, short s)
{
	t_envv	*ret;
	t_envv	*tmp;

	if (envv && name && (tmp = get_tenvv(envv, name)))
	{
		ft_strdel(&tmp->value);
		if (val)
			tmp->value = ft_strdup(val);
		return (envv);
	}
	if (!name || !(ret = new_tenvv(s)))
		return (envv);
	if (!(ret->name = ft_strdup(name))
		|| (val && !(ret->value = ft_strdup(val))))
	{
		del_tenvv(ret);
		return (envv);
	}
	ret->next = envv;
	return (ret);
}

t_envv	*ft_new_envv_equ(t_envv *envv, char *eq, short status)
{
	char *value;
	char *name;

	if (ft_isequal(eq))
	{
		name = ft_split_equal(eq, &value);
		return (ft_new_envv(envv, name, value, status));
	}
	return (NULL);
}

t_envv	*ft_setenv(t_envv *envv, char **t, int mode, short status)
{
	int		i;

	i = 0;
	while (t[i])
	{
		if (ft_isequal(t[i]))
			envv = ft_new_envv_equ(envv, t[i], status);
		else if (t[i + 1] && mode)
		{
			envv = ft_new_envv(envv, t[i], t[i + 1], status);
			i++;
		}
		else
			warning("uninitialised value", t[i]);
		i++;
	}
	return (envv);
}
