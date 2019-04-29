/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_utility.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stdenis <stdenis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/08 12:33:14 by stdenis           #+#    #+#             */
/*   Updated: 2019/04/27 20:05:54 by fstadelw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "ft_printf.h"
#include "shell42.h"
#include "get_input.h"

static void	print_var(const char *val)
{
	size_t	i;

	ft_printf("\"");
	i = 0;
	while (val[i] != '\0')
	{
		if (val[i] == '\"')
			ft_putchar('\\');
		ft_putchar(val[i]);
		i++;
	}
	ft_printf("\"\n");
}

void		print_for_alias(t_envv *node)
{
	if (isatty(1))
	{
		ft_printf("\033[1;32m\033[04m%s\033[00m=", node->name);
		print_var(node->value);
	}
	else
	{
		ft_printf("%s=", node->name);
		print_var(node->value);
	}
}

void		print_for_export_p(t_envv *node)
{
	if (isatty(1))
	{
		if (ft_strlen(node->value) > 0)
		{
			ft_printf("export \033[1;32m\033[04m%s\033[00m=", node->name);
			print_var(node->value);
		}
		else if (node->status & EXP)
			ft_printf("export \033[1;32m\033[04m%s\033[00m=\"\"\n", node->name);
		else
			ft_printf("export \033[1;32m\033[04m%s\033[00m\n", node->name);
	}
	else
	{
		if (ft_strlen(node->value) > 0)
		{
			ft_printf("export %s=", node->name);
			print_var(node->value);
		}
		else if (node->status & EXP)
			ft_printf("export %s=\"\"\n", node->name);
		else
			ft_printf("export %s\n", node->name);
	}
}

void		print_for_export(t_envv *node)
{
	if (isatty(1))
	{
		if (ft_strlen(node->value) > 0)
		{
			ft_printf("\033[1;32m\033[04m%s\033[00m=", node->name);
			print_var(node->value);
		}
		else if (node->status & EXP)
			ft_printf("\033[1;32m\033[04m%s\033[00m=\"\"\n", node->name);
		else
			ft_printf("\033[1;32m\033[04m%s\033[00m\n", node->name);
	}
	else
	{
		if (ft_strlen(node->value) > 0)
		{
			ft_printf("%s=", node->name);
			print_var(node->value);
		}
		else if (node->status & EXP)
			ft_printf("%s=\"\"\n", node->name);
		else
			ft_printf("%s\n", node->name);
	}
}
