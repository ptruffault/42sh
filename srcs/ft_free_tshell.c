/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_tshell.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptruffau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/08 15:26:10 by ptruffau          #+#    #+#             */
/*   Updated: 2019/03/26 17:21:55 by stdenis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell42.h"

void	ft_free_tshell(t_shell *sh)
{
	sh->env = ft_free_tenvv(sh->env);
	sh->alias = ft_free_tenvv(sh->alias);
	sh->process = ft_free_tprocess(sh->process);
	sh->hist = ft_free_thist(sh->hist);
	ft_strdel(&sh->clipboard);
	ft_strdel(&sh->txt);
}
