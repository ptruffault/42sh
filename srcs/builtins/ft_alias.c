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

void	ft_alias(t_shell *sh, char **argv)
{
	int i;

	i = 1;
	if (argv[1] == NULL)
		ft_puttenvv(sh->alias, EXP);
	else
	{
		while (argv[i])
		{
			if (ft_isequal(argv[i])
				&& !(ft_strchr(ft_strchr(argv[i], '='), '/')))
				sh->alias = ft_new_envv_equ(sh->alias, argv[i], EXP);
			else if (argv[i + 1] && !ft_strchr(argv[i + 1], '/'))
			{
				sh->alias = ft_new_envv(sh->alias, argv[i], argv[i + 1], EXP);
				i++;
			}
			i++;
		}
	}
}
