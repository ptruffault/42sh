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

int			check_builtin(char *input)
{
	t_shell	*sh;
	int		i;

	i = 0;
	sh = ft_get_set_shell(NULL);
	if (input == NULL)
		return (0);
	while (sh->builtins[i])
	{
		if (ft_strequ(sh->builtins[i++], input))
		{
			if (!sh->interactive 
				&& (ft_strequ(input, "alias") || ft_strequ(input, "alias")))
				return (0);
			return (1);
		}
	}
	return (0);
}
