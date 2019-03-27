/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   char.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stdenis <stdenis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/25 15:01:04 by stdenis           #+#    #+#             */
/*   Updated: 2019/03/08 17:52:26 by stdenis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	fill_with_char(const unsigned char value, t_printf *ptab, char fill)
{
	while (!(ptab->arg.flag & MINUS) && ptab->arg.larg-- > 0)
		fill_buffer(fill, ptab);
	fill_buffer(value, ptab);
	while ((ptab->arg.flag & MINUS) && ptab->arg.larg-- > 0)
		fill_buffer(fill, ptab);
}

static void	check_char(const unsigned char value, t_printf *ptab)
{
	size_t		len;

	len = 1;
	if (ptab->arg.flag & PREC)
		len = ((int)len < ptab->arg.prec) ? 1 : ptab->arg.prec;
	ptab->arg.larg -= (ptab->arg.larg > 0) ? len : 0;
	if (ptab->arg.flag & ZERO && !(ptab->arg.flag & MINUS))
		fill_with_char(value, ptab, '0');
	else
		fill_with_char(value, ptab, ' ');
}

void		get_char(va_list ap, void *ptr)
{
	t_printf	*tab;
	int			character;

	tab = (t_printf*)ptr;
	character = va_arg(ap, int);
	if (character >= 0 && character <= 200)
		check_char((unsigned char)character, tab);
}
