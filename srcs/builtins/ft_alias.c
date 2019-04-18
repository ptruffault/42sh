/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_alias.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptruffau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/08 12:43:00 by ptruffau          #+#    #+#             */
/*   Updated: 2019/03/26 17:21:55 by stdenis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell42.h"

static int		check_name_alias(const char *name)
{
	int		i;

	i = -1;
	while (name && name[++i] != '\0' && name[i] != '=')
	{
		if (ft_strchr("/\'\"$", name[i]))
		{
			error("alias: invalid alias name.", name);
			return (0);
		}
	}
	return (1);
}

static int		put_alias(t_shell *sh, char *str)
{
	char	*name;
	char	*val;
	char 	*tmp;

	if ((name = ft_split_equal(str, &val)) && !check_name_alias(name))
		return (1);
	if ((tmp = get_tenvv_val(ft_get_set_shell(NULL)->alias, val)))
		val = tmp;
	sh->alias = ft_new_envv(sh->alias, name, val, EXP);
	return (0);
}

int				ft_alias(t_shell *sh, char **argv)
{
	int		i;
	char	*tmp;

	i = 1;
	if (!argv[i])
		ft_puttenvv(sh->alias, EXP);
	while (argv[i])
	{
		if (ft_isequal(argv[i]))
		{
			if (put_alias(sh, argv[i]))
				return (1);
		}
		else if (argv[i + 1])
		{
			if (!check_name_alias(argv[i]))
				return (1);
			if ((tmp = get_tenvv_val(ft_get_set_shell(NULL)->alias, argv[i + 1])))
			{
				ft_strdel(&argv[i + 1]);
				argv[i + 1] = ft_strdup(tmp);
			}
			sh->alias = ft_new_envv(sh->alias, argv[i], argv[i + 1], EXP);
			i++;
		}
		i++;
	}
	return (0);
}
