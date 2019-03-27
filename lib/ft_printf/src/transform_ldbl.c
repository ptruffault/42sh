/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform_ldbl.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stdenis <stdenis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/04 14:55:36 by stdenis           #+#    #+#             */
/*   Updated: 2019/03/08 14:43:20 by stdenis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "double.h"

static long double	frxp(long double n, int *ex, t_dbl *tab_dbl)
{
	t_uniondbl	uni;

	uni.val = n;
	tab_dbl->sign = (uni.t_binary.sign & 1) ? 1 : 0;
	if (tab_dbl->sign == 1 && uni.val != 0)
		uni.val = -uni.val;
	if (uni.val == 0)
		return ((long double)0);
	*ex = uni.t_binary.exponent - 16383;
	uni.t_binary.exponent = 16383;
	return (uni.val);
}

static void			redirect_pointers_tab(t_dbl *tab_dbl, int exponent)
{
	int i;

	i = 0;
	while (i < 1999)
	{
		tab_dbl->numbers[i] = 0;
		i++;
	}
	if (exponent < 0)
	{
		tab_dbl->last = tab_dbl->numbers;
		tab_dbl->head = tab_dbl->numbers;
		tab_dbl->before_dot = tab_dbl->numbers;
	}
	else
	{
		tab_dbl->last = tab_dbl->numbers + 1000;
		tab_dbl->head = tab_dbl->numbers + 1000;
		tab_dbl->before_dot = tab_dbl->numbers + 1000;
	}
}

static void			h_ldbl_pos(t_dbl *tab_dbl, t_printf *ptab, int exponent)
{
	uint32_t	carry;
	uint64_t	value;
	int			power;

	while (exponent > 0)
	{
		carry = 0;
		power = (29 < exponent) ? 29 : exponent;
		tab_dbl->digits = tab_dbl->last - 1;
		while (tab_dbl->digits >= tab_dbl->head)
		{
			value = ((uint64_t)*tab_dbl->digits << power) + carry;
			*tab_dbl->digits = value % 1000000000;
			carry = value / 1000000000;
			tab_dbl->digits--;
		}
		if (carry)
			*--tab_dbl->head = carry;
		while (tab_dbl->last > tab_dbl->head && !tab_dbl->last[-1])
			tab_dbl->last--;
		exponent -= power;
	}
	calculate_nbr_integer(tab_dbl);
	rounding_ldbl(tab_dbl,ptab);
}

static void			h_ldbl_neg(t_dbl *tab_dbl, t_printf *ptab, int exponent)
{
	uint32_t	last;
	uint32_t	value;
	int			power;
	int			decal;

	while (exponent < 0)
	{
		last = 0;
		power = (9 < -exponent) ? 9 : -exponent;
		tab_dbl->digits = tab_dbl->head;
		decal = 4 + ((ptab->arg.prec + 9) / 9);
		while (tab_dbl->digits < tab_dbl->last)
		{
			value = *tab_dbl->digits & (1 << power) - 1;
			*tab_dbl->digits = (*tab_dbl->digits >> power) + last;
			last = (1000000000 >> power) * value;
			tab_dbl->digits++;
		}
		repos_pointers(tab_dbl, last, decal);
		exponent += power;
	}
	calculate_nbr_integer(tab_dbl);
	rounding_ldbl(tab_dbl,ptab);
}

void				transform_ldbl_80b(t_dbl *tab_dbl, t_printf *ptab)
{
	int		exponent;

	exponent = 0;
	tab_dbl->ldbl = frxp(tab_dbl->ldbl, &exponent, tab_dbl) * 2;
	if (tab_dbl->ldbl < 0)
		return ;
	if (tab_dbl->ldbl)
	{
		tab_dbl->ldbl *= 0x1p28;
		exponent -= 29;
	}
	redirect_pointers_tab(tab_dbl, exponent);
	*tab_dbl->last = tab_dbl->ldbl;
	tab_dbl->ldbl = 1000000000 * (tab_dbl->ldbl - *tab_dbl->last++);
	while (tab_dbl->ldbl)
	{
		*tab_dbl->last = tab_dbl->ldbl;
		tab_dbl->ldbl = 1000000000 * (tab_dbl->ldbl - *tab_dbl->last++);
	}
	if (exponent > 0)
		h_ldbl_pos(tab_dbl, ptab, exponent);
	else
		h_ldbl_neg(tab_dbl, ptab, exponent);
}
