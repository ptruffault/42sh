/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   octal.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stdenis <stdenis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/26 13:17:40 by stdenis           #+#    #+#             */
/*   Updated: 2019/03/08 17:58:45 by stdenis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	fill_oct(uintmax_t value, t_printf *ptab, char fill)
{
	bool print;

	print = true;
	if (ptab->arg.prec <= 0 && (ptab->arg.flag & PREC))
		print = false;
	if (value == 0 && (ptab->arg.flag & HASH) && ptab->arg.prec == 1)
		print = false;
	if (!print && ptab->arg.larg > 0 && value == 0)
		ptab->arg.larg++;
	while (!(ptab->arg.flag & MINUS) && ptab->arg.larg-- > 0)
		fill_buffer(fill, ptab);
	while (ptab->arg.prec-- > 0)
		fill_buffer('0', ptab);
	if (value != 0)
		putnbr_c(value, ptab, "01234567", 8);
	else if (print)
		fill_buffer('0',ptab);
	while ((ptab->arg.flag & MINUS) && ptab->arg.larg-- > 0)
		fill_buffer(fill,ptab);
}

static void	prepare_oct(uintmax_t value, t_printf *ptab)
{
	int		len;

	len = uint_length(value, 8);
	if (ptab->arg.flag & PREC)
		ptab->arg.prec = (len < ptab->arg.prec) ? ptab->arg.prec - len : 0;
	ptab->arg.larg -= len;
	ptab->arg.larg -= (ptab->arg.prec > 0) ? ptab->arg.prec : 0;
	if (ptab->arg.flag & HASH)
	{
		if (ptab->arg.prec <= 0)
		{
			ptab->arg.prec = (ptab->arg.prec <= 0) ? 1 : ptab->arg.prec;
			ptab->arg.larg--;
		}
	}
	if (check_flags(ptab->arg.flag, 2, ZERO, PREC) && !(ptab->arg.flag & MINUS))
		fill_oct(value, ptab, '0');
	else
		fill_oct(value, ptab, ' ');
}

void		check_octal(va_list ap, void *ptr)
{
	t_printf *tab;

	tab = (t_printf*)ptr;
	if (tab->arg.flag & H)
		prepare_oct((unsigned short int)va_arg(ap, uintmax_t), tab);
	else if (tab->arg.flag & HH)
		prepare_oct((unsigned char)va_arg(ap, uintmax_t), tab);
	else if (tab->arg.flag & L)
		prepare_oct((unsigned long int)va_arg(ap, uintmax_t), tab);
	else if (tab->arg.flag & LL)
		prepare_oct((unsigned long long int)va_arg(ap, uintmax_t), tab);
	else if (tab->arg.flag & J)
		prepare_oct(va_arg(ap, uintmax_t), tab);
	else if (tab->arg.flag & Z)
		prepare_oct((size_t)va_arg(ap, uintmax_t), tab);
	else
		prepare_oct((unsigned int)va_arg(ap, uintmax_t), tab);
}
