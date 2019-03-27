/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unsigned.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stdenis <stdenis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/05 19:00:26 by stdenis           #+#    #+#             */
/*   Updated: 2019/03/07 10:30:47 by stdenis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>
#include "ft_printf.h"

static void	fill_unsigned(uintmax_t value, t_printf *ptab, char fill)
{
	bool	print;

	print = true;
	if (value == 0 && ptab->arg.prec == 0 && ptab->arg.flag & PREC)
	{
		print = false;
		ptab->arg.larg++;
	}
	while (!(ptab->arg.flag & MINUS) && ptab->arg.larg-- > 0)
		fill_buffer(fill, ptab);
	while (ptab->arg.prec-- > 0)
		fill_buffer('0', ptab);
	if (print)
		putnbr_p(value, ptab);
	while ((ptab->arg.flag & MINUS) && ptab->arg.larg-- > 0)
		fill_buffer(fill, ptab);
}

void		prepare_un(uintmax_t value, t_printf *ptab)
{
	int		len;

	len = uint_length(value, 10);
	if (ptab->arg.flag & PREC)
	{
		ptab->arg.flag &= ~(ZERO);
		ptab->arg.prec = (len < ptab->arg.prec) ? ptab->arg.prec - len : 0;
	}
	ptab->arg.larg -= len;
	ptab->arg.larg -= (ptab->arg.prec > 0) ? ptab->arg.prec : 0;
	if (ptab->arg.flag & ZERO)
		fill_unsigned(value, ptab, '0');
	else
		fill_unsigned(value, ptab, ' ');
}

void		check_unsigned_integer(va_list ap, void *ptr)
{
	t_printf *tab;

	tab = (t_printf*)ptr;
	if (tab->arg.flag & H)
		prepare_un((unsigned short int)va_arg(ap, uintmax_t), tab);
	else if (tab->arg.flag & HH)
		prepare_un((unsigned char)va_arg(ap, uintmax_t), tab);
	else if (tab->arg.flag & L)
		prepare_un((unsigned long int)va_arg(ap, uintmax_t), tab);
	else if (tab->arg.flag & LL)
		prepare_un((unsigned long long int)va_arg(ap, uintmax_t), tab);
	else if (tab->arg.flag & J)
		prepare_un(va_arg(ap, uintmax_t), tab);
	else if (tab->arg.flag & Z)
		prepare_un((size_t)va_arg(ap, uintmax_t), tab);
	else
		prepare_un((unsigned int)va_arg(ap, uintmax_t), tab);
}
