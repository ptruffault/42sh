/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptruffau <ptruffau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/08 12:33:14 by ptruffau          #+#    #+#             */
/*   Updated: 2019/04/27 18:54:18 by fstadelw         ###   ########.fr       */
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
		if (argv[i][1] == '-')
			break ;
		while (argv[i][++j] != '\0')
		{
			if (argv[i][j] != 'p')
			{
				error_c("export: bad option :", argv[i][j]);
				ft_putendl_fd("usage: export [-p] [name[=value] ...]", 2);
				return (-2);
			}
		}
	}
	if (argv[i] && argv[i][1] == '-')
		++i;
	return (i);
}

static t_envv	*handler_env(t_shell *sh, char *name, char *val, bool equal)
{
	t_envv	*tmp;

	if (sh->env && (tmp = get_tenvv(sh->env, name)))
	{
		if ((!equal && tmp->status != NF) || equal)
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
			sh->env = ft_new_envv(sh->env, name, val, NF);
	}
	return (sh->env);
}

static int		export_option_p(t_shell *sh, char **a, int i)
{
	t_envv	*t;
	char	*val;
	bool	equal;

	val = NULL;
	equal = false;
	if (a[i--] == 0)
		ft_puttenvv(sh->env, (EXP | NF), 2);
	while (a[++i])
	{
		if (ft_isequal_env(a[i]))
		{
			equal = true;
			if ((a[i] = ft_split_equal(a[i], &val)) && !check_name(a[i]))
				return (1);
		}
		if ((t = get_tenvv(sh->env, a[i])))
		{
			t->status = EXP;
			print_for_export_p(t);
		}
		else if (check_name(a[i]))
			sh->env = handler_env(sh, a[i], val, equal);
	}
	return (0);
}

int				check_name(const char *name)
{
	int		i;

	i = -1;
	if (name && ft_isdigit(name[0]))
	{
		error("identifier must not begin by digit.", name);
		return (0);
	}
	while (name && name[++i] != '\0' && name[i] != '=')
	{
		if (ft_strchr("#@%$&<\'\">?:./[]{}()+*^!~|\\-", name[i]))
		{
			error("identifier not valid in this context.", name);
			return (0);
		}
	}
	return (1);
}

int				ft_export(t_shell *sh, char **argv)
{
	int		i;
	char	*name;
	char	*val;

	if (!*argv)
		ft_puttenvv(sh->env, (EXP | NF), 1);
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
