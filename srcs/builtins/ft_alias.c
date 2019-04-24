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
			error("alias: invalid alias name :", name);
			return (0);
		}
	}
	return (1);
}

static int		put_alias(t_shell *sh, char *str)
{
	char	*name;
	char	*val;

	if ((name = ft_split_equal(str, &val)) && !check_name_alias(name))
		return (1);
	sh->alias = ft_new_envv(sh->alias, name, val, EXP);
	return (0);
}

static int		print_alias(t_shell *sh, char *str)
{
	t_envv *alias;

	if (!(alias = get_tenvv(sh->alias, str)))
	{
		ft_putstr_fd("alias: ", 2);
		ft_putstr_fd(str, 2);
		ft_putendl_fd(" not found", 2);
		return (1);
	}
	print_for_alias(alias);
	return (0);
}

static int	error_options_alias(int ret, const char *opts)
{
	error("alias: invalid option :", opts);
	ft_putendl_fd("usage: alias [name[=value] ... ]", 2);
	return (ret);
}

int				ft_alias(t_shell *sh, char **argv)
{
	int		i;
	int		ret;

	i = 1;
	ret = 0;
	if (!argv[i])
		ft_puttenvv(sh->alias, EXP, 3);
	else if (argv[i][0] == '-')
		return (error_options_alias(2, argv[i]));
	while (argv[i])
	{
		if (ft_isequal(argv[i]))
			ret += put_alias(sh, argv[i]);
		else
			ret += print_alias(sh, argv[i]);
		i++;
	}
	ret = (ret > 0) ? 1 : 0;
	return (ret);
}
