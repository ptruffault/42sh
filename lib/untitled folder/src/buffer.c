/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buffer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stdenis <stdenis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/25 13:33:17 by stdenis           #+#    #+#             */
/*   Updated: 2019/03/07 15:58:09 by stdenis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	fill_buffer(char c, t_printf *ptab)
{
	if (ptab->buff == 2047)
	{
		write(1, ptab->buffer, ptab->buff);
		ft_memset(ptab->buffer, '\0', 2048);
		ptab->buff = 0;
		ptab->buffer[ptab->buff] = c;
	}
	else
		ptab->buffer[ptab->buff] = c;
	++ptab->buff;
	++ptab->rtn;
}
