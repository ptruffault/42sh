/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   double_print.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stdenis <stdenis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/11 15:57:05 by stdenis           #+#    #+#             */
/*   Updated: 2019/03/11 16:10:14 by stdenis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "double.h"

static void	print_decimal(t_dbl *tab_dbl, t_printf *ptab)
{
	int		len;
	int		i;

	while (tab_dbl->digits < tab_dbl->last && ptab->arg.prec > 0)
	{
		i = 0;
		len = (int)int_length(*tab_dbl->digits, 10);
		while (len + i < 9 && (ptab->arg.prec - i++) > 0)
			fill_buffer('0', ptab);
		ptab->arg.prec -= i;
		while (len > ptab->arg.prec && len--)
			*tab_dbl->digits = (*tab_dbl->digits / 10);
		if (ptab->arg.prec > 0)
			putnbr_p(*tab_dbl->digits, ptab);
		ptab->arg.prec -= len;
		tab_dbl->digits++;
	}
}

static void	printing_ldbl(t_dbl *tab_dbl, t_printf *ptab)
{
	size_t	len;

	while (tab_dbl->digits <= tab_dbl->before_dot)
	{
		len = int_length(*tab_dbl->digits, 10);
		while (tab_dbl->digits != tab_dbl->head && len++ < 9)
			fill_buffer('0', ptab);
		putnbr_p(*tab_dbl->digits, ptab);
		tab_dbl->digits++;
	}
	if (ptab->arg.prec > 0 || (ptab->arg.flag & HASH))
		fill_buffer('.', ptab);
	print_decimal(tab_dbl, ptab);
}

void		print_flags_ldbl(t_dbl *tab_dbl, t_printf *ptab, char fill)
{
	if (check_flags(ptab->arg.flag, 1, PLUS, ZERO) && tab_dbl->sign == 0)
		fill_buffer('+', ptab);
	if (check_flags(ptab->arg.flag, 1, SPACE, ZERO) && tab_dbl->sign == 0)
		fill_buffer(' ', ptab);
	if ((ptab->arg.flag & ZERO) && tab_dbl->sign == 1)
		fill_buffer('-', ptab);
	while (!(ptab->arg.flag & MINUS) && ptab->arg.larg-- > 0)
		fill_buffer(fill, ptab);
	if (check_flags(ptab->arg.flag, 2, SPACE, ZERO) && tab_dbl->sign == 0)
		fill_buffer(' ', ptab);
	if (check_flags(ptab->arg.flag, 2, PLUS, ZERO) && tab_dbl->sign == 0)
		fill_buffer('+', ptab);
	if (tab_dbl->sign == 1 && !(ptab->arg.flag & ZERO))
		fill_buffer('-', ptab);
	printing_ldbl(tab_dbl, ptab);
	while (ptab->arg.prec-- > 0)
		fill_buffer('0', ptab);
	while ((ptab->arg.flag & MINUS) && ptab->arg.larg-- > 0)
		fill_buffer(fill, ptab);
}

void		print_zero(t_printf *ptab, char fill, t_dbl *tab_dbl)
{
	if (check_flags(ptab->arg.flag, 1, PLUS, ZERO) && tab_dbl->sign == 0)
		fill_buffer('+', ptab);
	if (check_flags(ptab->arg.flag, 1, SPACE, ZERO) && tab_dbl->sign == 0)
		fill_buffer(' ', ptab);
	if ((ptab->arg.flag & ZERO) && tab_dbl->sign == 1)
		fill_buffer('-', ptab);
	while (!(ptab->arg.flag & MINUS) && ptab->arg.larg-- > 0)
		fill_buffer(fill, ptab);
	if (check_flags(ptab->arg.flag, 2, SPACE, ZERO) && tab_dbl->sign == 0)
		fill_buffer(' ', ptab);
	if (check_flags(ptab->arg.flag, 2, PLUS, ZERO) && tab_dbl->sign == 0)
		fill_buffer('+', ptab);
	if (tab_dbl->sign == 1 && !(ptab->arg.flag & ZERO))
		fill_buffer('-', ptab);
	fill_buffer('0', ptab);
	if (ptab->arg.prec > 0 || (ptab->arg.flag & HASH))
		fill_buffer('.', ptab);
	while (ptab->arg.prec-- > 0)
		fill_buffer('0', ptab);
	while ((ptab->arg.flag & MINUS) && ptab->arg.larg-- > 0)
		fill_buffer(fill, ptab);
}
