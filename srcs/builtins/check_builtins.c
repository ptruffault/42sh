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

static void	ft_init_builtins_tab(char *builtins[17])
{
	builtins[0] = "exit";
	builtins[1] = "cd";
	builtins[2] = "export";
	builtins[3] = "unset";
	builtins[4] = "alias";
	builtins[5] = "unalias";
	builtins[6] = "echo";
	builtins[7] = "set";
	builtins[8] = "type";
	builtins[9] = "jobs";
	builtins[10] = "hi";
	builtins[11] = "fg";
	builtins[12] = "bg";
	builtins[13] = "fc";
	builtins[14] = NULL;
}

int			check_builtin(char *input)
{
	char	*builtins[17];
	int		i;

	i = 0;
	ft_init_builtins_tab(builtins);
	if (input == NULL)
		return (0);
	while (i < 18 && builtins[i])
		if (ft_strequ(builtins[i++], input))
			return (1);
	return (0);
}
