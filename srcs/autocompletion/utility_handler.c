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

#include <stdlib.h>
#include "shell42.h"

int		check_before(char *str, int pos)
{
	char	*val;
	char	*tmp;
	char	*tmp2;

	if (!(val = ft_strndup(str, pos)))
		return (pos);
	tmp = val;
	tmp2 = val;
	if ((tmp2 = ft_strchr_end(tmp2, ';')))
		tmp = tmp2;
	if (tmp && ft_strchr(tmp, '='))
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

void	ft_arrdel(char ***arr)
{
	size_t	i;

	i = 0;
	while ((*arr)[i] != NULL)
	{
		free((*arr)[i]);
		i++;
	}
	free(*arr);
	*arr = NULL;
}
