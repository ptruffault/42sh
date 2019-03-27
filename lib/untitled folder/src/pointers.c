/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pointers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stdenis <stdenis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/26 14:11:34 by stdenis           #+#    #+#             */
/*   Updated: 2019/03/09 15:22:07 by stdenis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	fill_pointers(void *value, t_printf *ptab, char fill)
{
	bool		prec;

	prec = (ptab->arg.prec > 0 || !(ptab->arg.flag & PREC)) ? true : false;
	while (!(ptab->arg.flag & MINUS) && ptab->arg.larg-- > 0)
		fill_buffer(fill,ptab);
	if (!(ptab->arg.flag & ZERO))
	{
		fill_buffer('0',ptab);
		fill_buffer('x',ptab);
	}
	while (ptab->arg.prec-- > 0)
		fill_buffer('0',ptab);
	if (value == NULL && prec)
		fill_buffer('0', ptab);
	else
		putnbr_c((uintmax_t)value, ptab, "0123456789abcdef", 16);
	while ((ptab->arg.flag & MINUS) && ptab->arg.larg-- > 0)
		fill_buffer(fill, ptab);
}

static void	check_pointers(void *value, t_printf *ptab)
{
	int		len;
	char	fill;

	fill = ' ';
	if ((ptab->arg.flag & ZERO))
		fill = '0';
	len = uint_length((uintmax_t)value, 16);
	if (ptab->arg.flag & PREC)
		ptab->arg.prec = (len < ptab->arg.prec) ? ptab->arg.prec - len : 0;
	ptab->arg.larg -= len + 2;
	ptab->arg.larg -= (ptab->arg.prec > 0) ? ptab->arg.prec : 0;
	if ((ptab->arg.flag & ZERO))
	{
		fill = '0';
		fill_buffer('0', ptab);
		fill_buffer('x', ptab);
	}
	fill_pointers(value, ptab, fill);
}

void		get_pointers(va_list ap, void *ptr)
{
	t_printf *tab;

	tab = (t_printf*)ptr;
	check_pointers(va_arg(ap, void *), tab);
}
