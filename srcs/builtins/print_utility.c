/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_utility.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stdenis <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/08 12:33:14 by stdenis           #+#    #+#             */
/*   Updated: 2019/03/26 17:21:55 by stdenis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell42.h"

void    print_for_alias(t_envv	*node)
{
    if (isatty(1))
            ft_printf("alias \033[1;32m\033[04m%s\033[00m=\'%s\'\n", node->name, node->value);
    else
            ft_printf("alias %s=\'%s\'\n", node->name, node->value);
}

void    print_for_export(t_envv	*node, const char *opt)
{
    if (isatty(1))
    {
        if (ft_strlen(node->value) > 0)
            ft_printf("%s\033[1;32m\033[04m%s\033[00m=\"%s\"\n", opt, node->name, node->value);
        else if (node->status & EXP)
            ft_printf("%s\033[1;32m\033[04m%s\033[00m=\"\"\n", opt, node->name);
        else
            ft_printf("%s\033[1;32m\033[04m%s\033[00m\n", opt, node->name);
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