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

t_envv	*ft_export(t_shell *sh, char **argv)
{
	t_envv	*tmp;
	char	*name;
	char	*val;
	int		i;

	i = -1;
	if (!*argv)
		ft_puttenvv(sh->env, EXP);
	while (argv[++i])
	{
		if (ft_isequal(argv[i]))
		{
			name = ft_split_equal(argv[i], &val);
			sh->env = ft_new_envv(sh->env, name, val, EXP);
		}
		else if (sh->env && (tmp = get_tenvv(sh->env, argv[i])))
			tmp->status = EXP;
	}
	return (sh->env);
}
