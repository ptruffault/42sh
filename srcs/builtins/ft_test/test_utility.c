/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_utility.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stdenis <stdenis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/15 13:38:24 by stdenis           #+#    #+#             */
/*   Updated: 2019/03/17 18:34:45 by stdenis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell42.h"

int		return_fnc(char *str, int ret)
{
	printf("%s", str);
	return (ret);
}

int		check_integer_tab(char *argv)
{
	int		i;

	i = -1;
	while (argv[++i])
	{
		if (!(ft_isdigit(argv[i])))
			return (1);
	}
	return (0);
}
