/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_utility.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stdenis <stdenis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/08 12:33:14 by stdenis           #+#    #+#             */
/*   Updated: 2019/04/24 17:21:51 by fstadelw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "ft_printf.h"
#include "shell42.h"
#include "get_input.h"

void	print_for_alias(t_envv *node)
{
	if (isatty(1))
		ft_printf(ALIAS_1, node->name, node->value);
	else
		ft_printf("alias %s=\'%s\'\n", node->name, node->value);
}

void	print_for_export(t_envv *node, const char *opt)
{
	if (isatty(1))
	{
		if (ft_strlen(node->value) > 0)
			ft_printf(EXP_P1, opt, node->name, node->value);
		else if (node->status & EXP)
			ft_printf(EXP_P2, opt, node->name);
		else
			ft_printf(EXP_P3, opt, node->name);
	}
	else
	{
		if (ft_strlen(node->value) > 0)
			ft_printf("%s%s=\"%s\"\n", opt, node->name, node->value);
		else if (node->status & EXP)
			ft_printf("%s%s=\"\"\n", opt, node->name);
		else
			ft_printf("%s%s\n", opt, node->name);
	}
}
