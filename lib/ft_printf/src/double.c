/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   double.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stdenis <stdenis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/04 12:45:26 by stdenis           #+#    #+#             */
/*   Updated: 2019/03/11 12:57:32 by stdenis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "double.h"

static int	check_integrity(t_dbl *tab_dbl)
{
	t_binary	uni;
	int			exp;
	int			mant;

	uni.val = tab_dbl->ldbl;
	tab_dbl->sign = uni.t_bits.exposign >> 15;
	exp = uni.t_bits.exposign & 0x7fff;
	mant = uni.t_bits.mantissa >> 63;
	if (!exp && !mant)
		return (uni.t_bits.mantissa ? 0 : 1);
	if (!mant)
		return (2);
	if (exp == 0x7fff)
		return (uni.t_bits.mantissa << 1 ? 3 : 4);
	return (5);
}

void		check_float(va_list ap, void *ptr)
{
	t_dbl			tab_dbl;
	t_printf		*ptab;
	int				check;
	int				prec;

	ptab = (t_printf*)ptr;
	if (!(ptab->arg.flag & PREC))
		ptab->arg.prec = 6;
	prec = ptab->arg.prec;
	if (!(ptab->arg.flag & LDBL))
	{
		tab_dbl.dbl = va_arg(ap, double);
		tab_dbl.ldbl = (long double)tab_dbl.dbl;
	}
	else
		tab_dbl.ldbl = va_arg(ap, long double);
	check = check_integrity(&tab_dbl);
	if (check == 5)
	{
		transform_ldbl_80b(&tab_dbl, ptab);
		if (prec == 0)
			rounding_prec_zero(&tab_dbl, ptab);
	}
	else
		print_others(&tab_dbl, check, ptab);
}
