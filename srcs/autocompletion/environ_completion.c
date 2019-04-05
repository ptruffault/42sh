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

static int	environ_len(t_envv *envv)
{
	int		i;

	i = 0;
	while (envv)
	{
		i++;
		envv = envv->next;
	}
	return (i);
}

int		copy_env_tab(char *value, char **tabl, t_envv *envv, bool all)
{
	int		i;

	i = 0;
	while (envv)
	{
		if (all || (envv->name && (ft_str_startwith(envv->name, value))))
		{
			if (!(tabl[i] = ft_strdup(envv->name)))
				return (-1);
			i++;
		}
		envv = envv->next;
	}
	return (i);
}

char 	**get_environ_match(char *value, int *total, bool all)
{
	t_shell			*sh;
	char			**tabl;
	int				len_env;

	sh = ft_get_set_shell(NULL);
	len_env = environ_len(sh->env);
	if (!(tabl = (char**)malloc(sizeof(char*) * (len_env + 1))))
		return (NULL);
	set_null_tabl(tabl, len_env);
	tabl[len_env] = NULL;
	if ((*total = copy_env_tab(value, tabl, sh->env, all)) == -1)
		ft_arrdel(&tabl);
	return (tabl);
}
