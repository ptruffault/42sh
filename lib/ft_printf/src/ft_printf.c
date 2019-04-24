/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stdenis <stdenis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/25 13:32:02 by stdenis           #+#    #+#             */
/*   Updated: 2019/04/24 17:24:26 by fstadelw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "ft_printf.h"

void	set_struct(t_printf *ptab)
{
	ptab->fmt = 0;
	ptab->buff = 0;
	ptab->rtn = 0;
	ptab->dispatcher[0] = get_char;
	ptab->dispatcher[1] = get_string;
	ptab->dispatcher[2] = get_pointers;
	ptab->dispatcher[3] = check_integer;
	ptab->dispatcher[4] = check_octal;
	ptab->dispatcher[5] = check_unsigned_integer;
	ptab->dispatcher[6] = check_hexadecimal;
	ptab->dispatcher[7] = check_hexadecimal;
	ptab->dispatcher[8] = check_float;
	ptab->dispatcher[9] = get_string_uni;
	ptab->dispatcher[10] = get_char_uni;
	ptab->dispatcher[11] = check_binary;
	ptab->arg.type = 0;
	ptab->arg.larg = 0;
	ptab->arg.prec = 0;
	ptab->arg.flag = 0;
}

void	reset_arg(t_printf *ptab)
{
	ptab->arg.type ^= ptab->arg.type;
	ptab->arg.larg ^= ptab->arg.larg;
	ptab->arg.prec ^= ptab->arg.prec;
	ptab->arg.flag ^= ptab->arg.flag;
}

int		ft_printf(const char *format, ...)
{
	va_list		ap;
	t_printf	tab;

	if (format == NULL)
		return (1);
	va_start(ap, format);
	set_struct(&tab);
	while (check_arg(format, &tab, ap))
	{
		if (tab.arg.type == PERCENT)
			check_string("%", &tab);
		else if (tab.arg.type <= 11)
			tab.dispatcher[tab.arg.type](ap, &tab);
		reset_arg(&tab);
	}
	if (tab.buff > 0)
		write(1, tab.buffer, tab.buff);
	va_end(ap);
	return (tab.rtn);
}
