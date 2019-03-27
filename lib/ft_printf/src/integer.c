/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   integer.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stdenis <stdenis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/25 15:16:42 by stdenis           #+#    #+#             */
/*   Updated: 2019/03/08 18:40:25 by stdenis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>
#include "ft_printf.h"

static void	fill_integer_zero(intmax_t value, t_printf *ptab, char fill)
{
	if (ptab->arg.flag & SPACE && value >= 0)
		fill_buffer(' ',ptab);
	if (value < 0)
		fill_buffer('-',ptab);
	if (ptab->arg.flag & PLUS && value >= 0)
		fill_buffer('+',ptab);
	while (!(ptab->arg.flag & MINUS) && ptab->arg.larg-- > 0)
		fill_buffer(fill,ptab);
	while (ptab->arg.prec-- > 0)
		fill_buffer('0',ptab);
	if (value < 0)
		putnbr_n(value,ptab);
	else
		putnbr_p(value,ptab);
	while ((ptab->arg.flag & MINUS) && ptab->arg.larg-- > 0)
		fill_buffer(fill,ptab);
}

static void	fill_integer(intmax_t value, t_printf *ptab, char fill)
{
	bool	print;

	print = true;
	if (value == 0 && ptab->arg.prec == 0 && ptab->arg.flag & PREC)
	{
		print = false;
		ptab->arg.larg++;
	}
	while (!(ptab->arg.flag & MINUS) && ptab->arg.larg-- > 0)
		fill_buffer(fill,ptab);
	if (value >= 0 && ptab->arg.flag & SPACE)
		fill_buffer(' ',ptab);
	if (value >= 0 && ptab->arg.flag & PLUS)
		fill_buffer('+',ptab);
	else if (value < 0)
		fill_buffer('-',ptab);
	while (ptab->arg.prec-- > 0)
		fill_buffer('0',ptab);
	if (print && value < 0)
		putnbr_n(value,ptab);
	else if (print)
		putnbr_p(value,ptab);
	while ((ptab->arg.flag & MINUS) && ptab->arg.larg-- > 0)
		fill_buffer(fill,ptab);
}

static void	prepare_int(intmax_t value, t_printf *ptab)
{
	int		len;

	len = int_length(value, 10);
	if (ptab->arg.flag & PREC)
	{
		ptab->arg.flag &= ~(ZERO);
		ptab->arg.prec = (len < ptab->arg.prec) ? ptab->arg.prec - len : 0;
	}
	ptab->arg.larg -= len;
	ptab->arg.larg -= (ptab->arg.prec > 0) ? ptab->arg.prec : 0;
	if (ptab->arg.flag & PLUS && value >= 0)
	{
		ptab->arg.larg--;
		ptab->arg.flag &= ~(SPACE);
	}
	if (ptab->arg.flag & SPACE && value >= 0)
		ptab->arg.larg--;
	if (value < 0)
		ptab->arg.larg--;
	if (ptab->arg.flag & ZERO && !(ptab->arg.flag & MINUS))
		fill_integer_zero(value, ptab, '0');
	else
		fill_integer(value, ptab, ' ');
}

void		check_integer(va_list ap, void *ptr)
{
	t_printf *tab;

	tab = (t_printf*)ptr;
	if (tab->arg.flag & H && !(tab->arg.flag & Z) && !(tab->arg.flag & J))
		prepare_int((short int)va_arg(ap, intmax_t), tab);
	else if (tab->arg.flag & HH)
		prepare_int((char)va_arg(ap, intmax_t), tab);
	else if (tab->arg.flag & J)
		prepare_int(va_arg(ap, intmax_t), tab);
	else if (tab->arg.flag & Z)
		prepare_int((long int)va_arg(ap, intmax_t), tab);
	else if (tab->arg.flag & L)
		prepare_int((long int)va_arg(ap, intmax_t), tab);
	else if (tab->arg.flag & LL)
		prepare_int((long long int)va_arg(ap, intmax_t), tab);
	else
		prepare_int((int)va_arg(ap, intmax_t), tab);
}
