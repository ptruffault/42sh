/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_builtins.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptruffau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/08 12:41:39 by ptruffau          #+#    #+#             */
/*   Updated: 2019/03/26 17:21:55 by stdenis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell42.h"

static void	ft_init_builtins_tab(t_shell *sh)
{
	sh->builtins[0] = "exit";
	sh->builtins[1] = "cd";
	sh->builtins[2] = "export";
	sh->builtins[3] = "unset";
	sh->builtins[4] = "alias";
	sh->builtins[5] = "unalias";
	sh->builtins[6] = "echo";
	sh->builtins[7] = "set";
	sh->builtins[8] = "type";
	sh->builtins[9] = "jobs";
	sh->builtins[10] = "hi";
	sh->builtins[11] = "fg";
	sh->builtins[12] = "bg";
	sh->builtins[13] = "fc";
	sh->builtins[14] = "hash";
	sh->builtins[15] = "test";
	sh->builtins[16] = NULL;
}

int			check_builtin(char *input)
{
	t_shell	*sh;
	int		i;

	i = 0;
	sh = ft_get_set_shell(NULL);
	ft_init_builtins_tab(sh);
	if (input == NULL)
		return (0);
	while (sh->builtins[i])
		if (ft_strequ(sh->builtins[i++], input))
			return (1);
	return (0);
}
