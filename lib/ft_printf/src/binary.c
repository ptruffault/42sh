/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   binary.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stdenis <stdenis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/09 13:56:13 by stdenis           #+#    #+#             */
/*   Updated: 2019/03/09 14:00:18 by stdenis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	before_or_after(uintmax_t value, t_printf *ptab, char fill)
{
	while (!(ptab->arg.flag & (MINUS | ZERO)) && ptab->arg.larg-- > 0)
		fill_buffer(fill, ptab);
	if (ptab->arg.flag & HASH && value != 0)
		fill_buffer('0', ptab);
	if (ptab->arg.flag & HASH && value != 0)
		fill_buffer('b', ptab);
	while (check_flags(ptab->arg.flag, 2, ZERO, MINUS) && ptab->arg.larg-- > 0)
		fill_buffer(fill, ptab);
}

static void	fill_bin(uintmax_t value, t_printf *ptab, char fill)
{
	int		prec;

	prec = ptab->arg.prec;
	before_or_after(value, ptab, fill);
	while (ptab->arg.prec-- > 0)
		fill_buffer('0', ptab);
	if (value == 0)
	{
		if (((ptab->arg.flag & PREC) && prec > 0) || !(ptab->arg.flag & PREC))
			fill_buffer('0', ptab);
	}
	else
		putnbr_c(value, ptab, "01", 2);
	while ((ptab->arg.flag & MINUS) && ptab->arg.larg-- > 0)
		fill_buffer(fill, ptab);
}

static void	prepare_bin(uintmax_t value, t_printf *ptab)
{
	int		len;

	len = uint_length(value, 2);
	if (ptab->arg.flag & PREC)
	{
		ptab->arg.flag &= ~(ZERO);
		ptab->arg.prec = (len < ptab->arg.prec) ? ptab->arg.prec - len : 0;
	}
	ptab->arg.larg -= (value == 0) ? 0 : len;
	ptab->arg.larg -= (ptab->arg.prec > 0) ? ptab->arg.prec : 0;
	if (ptab->arg.flag & HASH && value != 0)
		ptab->arg.larg -= 2;
	if (ptab->arg.flag & ZERO && !(ptab->arg.flag & MINUS))
		fill_bin(value, ptab, '0');
	else
		fill_bin(value, ptab, ' ');
}

void		check_binary(va_list ap, void *ptr)
{
	t_printf *tab;

	tab = (t_printf*)ptr;
	if (tab->arg.flag & H)
		prepare_bin((unsigned short int)va_arg(ap, uintmax_t), tab);
	else if (tab->arg.flag & HH)
		prepare_bin((unsigned char)va_arg(ap, uintmax_t), tab);
	else if (tab->arg.flag & L)
		prepare_bin((unsigned long int)va_arg(ap, uintmax_t), tab);
	else if (tab->arg.flag & LL)
		prepare_bin((unsigned long long int)va_arg(ap, uintmax_t), tab);
	else if (tab->arg.flag & J)
		prepare_bin(va_arg(ap, uintmax_t), tab);
	else if (tab->arg.flag & Z)
		prepare_bin((size_t)va_arg(ap, uintmax_t), tab);
	else
		prepare_bin((unsigned int)va_arg(ap, uintmax_t), tab);
}
