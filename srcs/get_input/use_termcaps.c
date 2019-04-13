/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adi-rosa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/05 12:31:56 by adi-rosa          #+#    #+#             */
/*   Updated: 2019/03/26 17:21:55 by stdenis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <get_input.h>

int	term_actions(const char *cmd)
{
	if (!(cmd = (tgetstr(cmd, NULL))))
		return (FAILURE);
	ft_putstr(cmd);
	return (SUCCESS);
}

int	term_goto(char *cmd, int row, int col)
{
	if (!(cmd = tgetstr(cmd, NULL)))
		return (FAILURE);
	ft_putstr(tgoto(cmd, row, col));
	return (SUCCESS);
}
