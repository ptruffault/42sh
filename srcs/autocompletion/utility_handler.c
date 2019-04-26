/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stdenis <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/18 15:33:46 by stdenis           #+#    #+#             */
/*   Updated: 2019/03/26 17:18:36 by stdenis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell42.h"

int		check_before(char *str, int pos)
{
	char	*val;

	if (!(val = ft_strndup(str, pos)))
		return (pos);
	if (ft_strchr(val, '='))
	{
		ft_strdel(&val);
		return (0);
	}
	ft_strdel(&val);
	return (pos);
}

char	*check_tilde(char *value)
{
	char	*tmp;
	char	*ret;
	char	*home;
	t_shell	*sh;

	ret = value;
	sh = ft_get_set_shell(NULL);
	if ((tmp = ft_strchr(value, '~')))
	{
		if (!(home = retrieve_home(NULL, sh->env)))
			return (value);
		if (!(value = ft_strpull(value, tmp, 0, home)))
		{
			ft_strdel(&ret);
			return (NULL);
		}
		ft_strdel(&ret);
		return (value);
	}
	return (ret);
}
