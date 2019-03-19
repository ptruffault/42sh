/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptruffau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/04 14:10:52 by ptruffau          #+#    #+#             */
/*   Updated: 2019/03/19 13:49:05 by stdenis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <shell42.h>

int		ft_echo(char **input)
{
	int i;
	int opts_n;

	i = 0;
	opts_n = 0;
	if (*input && ft_strequ(input[i], "-n") && input[++i])
		opts_n = 1;
	while (input && input[i])
	{
		if (i > opts_n)
			ft_putstr("    ");
		ft_putstr(input[i++]);
	}
	if (opts_n)
		ft_putchar(0);
	else
		ft_putchar('\n');
	return (0);
}
