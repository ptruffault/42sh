/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_double.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stdenis <stdenis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/05 09:22:38 by stdenis           #+#    #+#             */
/*   Updated: 2019/03/08 18:15:33 by stdenis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "double.h"

static void	prepare_print(t_dbl *tab_dbl, t_printf *ptab)
{
	int			minus;

	if (tab_dbl->last > tab_dbl->digits + 1)
		tab_dbl->last = tab_dbl->digits + 1;
	while (tab_dbl->last > tab_dbl->head && !tab_dbl->last[-1])
		tab_dbl->last--;
	tab_dbl->digits = tab_dbl->head;
	if (tab_dbl->head > tab_dbl->before_dot)
		tab_dbl->head = tab_dbl->before_dot;
	minus = (ptab->arg.prec > 0) ? 1 : 0;
	minus += (ptab->arg.flag & SPACE && tab_dbl->sign == 0) ? 1 : 0;
	minus += (ptab->arg.flag & PLUS && tab_dbl->sign == 0) ? 1 : 0;
	minus += (tab_dbl->sign == 1) ? 1 : 0;
	minus += (ptab->arg.prec == 0 && ptab->arg.flag & HASH) ? 1 : 0;
	ptab->arg.larg -= 1 + tab_dbl->integer + ptab->arg.prec + minus;
	tab_dbl->digits = tab_dbl->head;
	if (ptab->arg.flag & PLUS)
		ptab->arg.flag &= ~(SPACE);
	if (ptab->arg.flag & ZERO)
		print_flags_ldbl(tab_dbl, ptab, '0');
	else
		print_flags_ldbl(tab_dbl, ptab, ' ');
}

void		calculate_nbr_integer(t_dbl *tab_dbl)
{
	unsigned int	i;

	i = 10;
	if (tab_dbl->head < tab_dbl->last)
	{
		tab_dbl->integer = 9 * (tab_dbl->before_dot - tab_dbl->head);
		while (*tab_dbl->head >= i)
		{
			tab_dbl->integer++;
			i *= 10;
		}
	}
	else
		tab_dbl->integer = 0;
}

void		print_others(t_dbl *tab_dbl, int check, t_printf *ptab)
{
	int		minus;

	if (check == 4 && tab_dbl->sign == 1)
		check_string("-inf", ptab);
	else if (check == 4 && tab_dbl->sign == 0)
		check_string("inf", ptab);
	else if (check == 3)
		check_string("nan", ptab);
	else
	{
		minus = (ptab->arg.prec > 0) ? 1 : 0;
		minus += (ptab->arg.flag & SPACE && tab_dbl->sign == 0) ? 1 : 0;
		minus += (ptab->arg.flag & PLUS && tab_dbl->sign == 0) ? 1 : 0;
		minus += (tab_dbl->sign == 1) ? 1 : 0;
		minus += (ptab->arg.prec == 0 && ptab->arg.flag & HASH) ? 1 : 0;
		ptab->arg.larg -= 1 + minus + ptab->arg.prec;
		if (ptab->arg.flag & ZERO)
			print_zero(ptab, '0', tab_dbl);
		else
			print_zero(ptab, ' ', tab_dbl);
	}
}

void		repos_pointers(t_dbl *tab_dbl, uint32_t last, int decal)
{
	uint32_t	*ptr;

	if (!*tab_dbl->head)
		tab_dbl->head++;
	if (last)
		*tab_dbl->last++ = last;
	ptr = tab_dbl->before_dot;
	if (tab_dbl->last - ptr > decal)
		tab_dbl->last = ptr + decal;
}

void		rounding_ldbl(t_dbl *tab_dbl, t_printf *ptab)
{
	int			prec;
	int			j;
	int			i;

	prec = (ptab->arg.prec > 10000) ? 10000 : ptab->arg.prec;
	tab_dbl->digits = tab_dbl->before_dot + 1 + (prec / 9);
	j = ((ptab->arg.prec) % 9) + 1;
	i = 10;
	while (j++ < 9)
		i *= 10;
	tab_dbl->rounding = *tab_dbl->digits % i;
	if (tab_dbl->rounding && tab_dbl->digits + 1 != tab_dbl->last)
	{
		if (tab_dbl->rounding / (i / 10) >= 5)
			*tab_dbl->digits = (*tab_dbl->digits - tab_dbl->rounding) + i;
		while (*tab_dbl->digits > 999999999)
		{
			*tab_dbl->digits-- = 0;
			if (tab_dbl->digits < tab_dbl->head)
				*--tab_dbl->head = 0;
			(*tab_dbl->digits)++;
		}
		calculate_nbr_integer(tab_dbl);
	}
	prepare_print(tab_dbl, ptab);
}
