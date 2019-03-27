/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbrs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stdenis <stdenis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/26 13:55:31 by stdenis           #+#    #+#             */
/*   Updated: 2019/03/11 18:30:26 by stdenis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>
#include "ft_printf.h"

bool	check_flags(t_flags flag, int m, t_flags f, t_flags s)
{
	if (m == 1 && (flag & f) && (flag & s))
		return (true);
	else if (m == 2 && (flag & f) && !(flag & s))
		return (true);
	else if (m == 3 && !(flag & f) && !(flag & s))
		return (true);
	return (false);
}

void	putnbr_c(uintmax_t res, t_printf *ptab, char *base, int bl)
{
	uintmax_t	rtn;

	if (res > 0)
	{
		if (bl == 8)
			putnbr_c((res >> 3), ptab, base, bl);
		else if (bl == 16)
			putnbr_c((res >> 4), ptab, base, bl);
		else if (bl == 2)
			putnbr_c((res >> 1), ptab, base, bl);
	}
	if (res != 0)
	{
		rtn = res & (bl - 1);
		fill_buffer(base[rtn], ptab);
	}
}

int		uint_length(uintmax_t value, int base)
{
	size_t	i;

	i = 0;
	while (value > 0)
	{
		i++;
		value /= base;
	}
	return ((i == 0) ? 1 : i);
}

void	putnbr_p(uintmax_t res, t_printf *ptab)
{
	uintmax_t mod;
	uintmax_t p;

	mod = 0;
	p = 0;
	if (res > 9)
	{
		mod = res / 10;
		putnbr_p(mod, ptab);
		p = (mod << 3) + (mod << 1);
		mod = res - p;
		fill_buffer((mod) + '0',ptab);
	}
	else
		fill_buffer(res + '0',ptab);
}

void	putnbr_n(intmax_t res, t_printf *ptab)
{
	intmax_t mod;
	intmax_t p;

	mod = 0;
	p = 0;
	if (res < -9)
	{
		mod = res / 10;
		putnbr_n(mod, ptab);
		p = (mod << 3) + (mod << 1);
		mod = res - p;
		fill_buffer(-(mod) + '0',ptab);
	}
	else if (res <= 0)
		fill_buffer((-res) + '0',ptab);
}
