/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tab_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptruffau <ptruffau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/07 16:41:00 by ptruffau          #+#    #+#             */
/*   Updated: 2019/04/24 16:57:38 by fstadelw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int			ft_check_in_tab(char **tabl, char *str)
{
	int i;

	i = -1;
	while (++i < 100)
		if (ft_strequ(tabl[i], str))
			return (0);
	return (1);
}

void		ft_reset_tab(char **tabl)
{
	int i;

	i = -1;
	while (++i < 100)
		tabl[i] = NULL;
}