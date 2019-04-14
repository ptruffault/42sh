/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptruffau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/08 12:33:14 by ptruffau          #+#    #+#             */
/*   Updated: 2019/03/26 17:21:55 by stdenis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell42.h"

static int		check_options(char **argv)
{
	int		i;
	int		j;

	i = -1;
	if (!*argv || (*argv && argv[0][0] != '-'))
		return (i);
	while (argv[++i] && argv[i][0] == '-')
	{
		j = 0;
		while (argv[i][++j] != '\0')
		{
			if (argv[i][j] != 'p')
			{
				error("export: bad options.", NULL);
				return (-2);
			}
		}
	}
	return (i);
}

static t_envv	*handler_env(t_shell *sh, char *name, char *val, bool equal)
{
	t_envv	*tmp;

	if (sh->env && (tmp = get_tenvv(sh->env, name)))
	{
		if ((!equal && tmp->status != TMP) || equal)
			tmp->status = EXP;
		if (val)
		{
			ft_strdel(&tmp->value);
			tmp->value = ft_strdup(val);
		}
		if (!tmp->value)
			tmp->value = ft_strnew(0);
	}
	else
	{
		if (equal)
			sh->env = ft_new_envv(sh->env, name, val, EXP);
		else
			sh->env = ft_new_envv(sh->env, name, val, TMP);
	}
	return (sh->env);
}

static int		export_option_p(t_shell *sh, char **argv, int i)
{
	t_envv	*t;
	char	*name;
	char	*val;
	bool	equal;

	val = NULL;
	equal = false;
	if (argv[i] == 0)
		ft_puttenvv(sh->env, (EXP | TMP));
	while (argv[i])
	{
		name = argv[i];
		if (ft_isequal_env(name))
		{
			equal = true;
			if ((name = ft_split_equal(argv[i], &val)) && !check_name(name))
				return (1);
		}
		if ((t = get_tenvv(sh->env, name)))
			ft_printf("\033[1;32m\033[04m%s\033[00m=%s\n", t->name, t->value);
		else if (check_name(name))
			sh->env = handler_env(sh, name, val, equal);
		i++;
	}
	return (0);
}

int				check_name(const char *name)
{
	int		i;

	i = -1;
	if (name && ft_isdigit(name[0]))
	{
		error("identifier not valid in this context.", name);
		return (0);
	}
	while (name && name[++i] != '\0' && name[i] != '=')
	{
		if (ft_strchr("#@%$&<>?:./[]{}()+*^!~|\\-", name[i]))
		{
			error("identifier not valid in this context.", name);
			return (0);
		}
	}
	return (1);
}

int			ft_export(t_shell *sh, char **argv)
{
	int		i;
	char	*name;
	char	*val;

	if (!*argv)
		ft_puttenvv(sh->env, (EXP | TMP));
	if ((i = check_options(argv)) == -2)
		return (2);
	else if (i >= 0)
		return (export_option_p(sh, argv, i));
	val = NULL;
	while (argv[++i])
	{
		name = argv[i];
		if (ft_isequal_env(name))
		{
			if ((name = ft_split_equal(argv[i], &val)) && !check_name(name))
				return (1);
			sh->env = handler_env(sh, name, val, true);
		}
		else
			sh->env = handler_env(sh, name, val, false);
	}
	return (0);
}
