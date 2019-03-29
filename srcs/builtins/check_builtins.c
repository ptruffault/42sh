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

static void	ft_init_builtins_tab(char *builtins[18])
{
	builtins[0] = "setenv";
	builtins[1] = "unsetenv";
	builtins[2] = "exit";
	builtins[3] = "cd";
	builtins[4] = "export";
	builtins[5] = "unset";
	builtins[6] = "alias";
	builtins[7] = "unalias";
	builtins[8] = "echo";
	builtins[9] = "set";
	builtins[10] = "type";
	builtins[11] = "jobs";
	builtins[12] = "env";
	builtins[13] = "hi";
	builtins[14] = "fg";
	builtins[15] = "bg";
	builtins[16] = "fc";
	builtins[17] = NULL;
}

int			check_builtin(char *input)
{
	char	*builtins[18];
	int		i;

	i = 0;
	ft_init_builtins_tab(builtins);
	if (input == NULL)
		return (0);
	while (i < 17 && builtins[i])
		if (ft_strequ(builtins[i++], input))
			return (1);
	return (0);
}
