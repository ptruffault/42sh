/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arguments.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stdenis <stdenis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/25 13:34:41 by stdenis           #+#    #+#             */
/*   Updated: 2019/03/09 15:24:36 by stdenis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int		bonus_printf(t_printf *ptab, char c)
{
	if ((c == 'S' || ((ptab->arg.flag & L) && c == 's')) && ++ptab->fmt)
		ptab->arg.type = SS;
	else if ((c == 'C' || ((ptab->arg.flag & L) && c == 'c')) && ++ptab->fmt)
		ptab->arg.type = CC;
	else if (c == 'b' && ++ptab->fmt)
		ptab->arg.type = B;
	else
		ptab->arg.type = 999;
	return (1);
}

static int		arg_printf(t_printf *ptab, char c)
{
	if (c == 'U' || c == 'O' || c == 'D')
		ptab->arg.flag = (ptab->arg.flag | L) & ~(H) & ~(HH);
	if (!(ptab->arg.flag & L) && c == 's' && ++ptab->fmt)
		ptab->arg.type = S;
	else if ((c == 'd' || c == 'i' || c == 'D') && ++ptab->fmt)
		ptab->arg.type = DI;
	else if (c == 'x' && ++ptab->fmt)
		ptab->arg.type = X;
	else if (c == 'X' && ++ptab->fmt)
		ptab->arg.type = XX;
	else if ((c == 'o' || c == 'O') && ++ptab->fmt)
		ptab->arg.type = O;
	else if ((c == 'u' || c == 'U') && ++ptab->fmt)
		ptab->arg.type = U;
	else if (c == 'p' && ++ptab->fmt)
		ptab->arg.type = P;
	else if (!(ptab->arg.flag & L) && c == 'c' && ++ptab->fmt)
		ptab->arg.type = C;
	else if (c == 'f' && ++ptab->fmt)
		ptab->arg.type = F;
	else if (c == '%' && ++ptab->fmt)
		ptab->arg.type = PERCENT;
	else
		return (bonus_printf(ptab, c));
	return (1);
}

static int		conv_flags(t_printf *ptab, const char *format)
{
	if (format[ptab->fmt] == 'h')
		if (ptab->arg.flag & H)
			ptab->arg.flag = (ptab->arg.flag | HH) & ~(H);
		else
			ptab->arg.flag = (ptab->arg.flag | H);
	else if (format[ptab->fmt] == 'l')
		if (ptab->arg.flag & L)
			ptab->arg.flag = (ptab->arg.flag | LL) & ~(L);
		else
			ptab->arg.flag = (ptab->arg.flag | L) & ~(H) & ~(HH);
	else if (format[ptab->fmt] == 'L')
		ptab->arg.flag = (ptab->arg.flag | LDBL);
	else if (format[ptab->fmt] == 'j')
		ptab->arg.flag = (ptab->arg.flag | J);
	else if (format[ptab->fmt] == 'z')
		ptab->arg.flag = (ptab->arg.flag | Z);
	else
		return (0);
	return (1);
}

static int		arg_flags(t_printf *ptab, const char *format)
{
	if (format[ptab->fmt] == '-')
		ptab->arg.flag = (ptab->arg.flag | MINUS) & ~(ZERO);
	else if (format[ptab->fmt] == '+')
		ptab->arg.flag = (ptab->arg.flag | PLUS) & ~(SPACE);
	else if (format[ptab->fmt] == '#')
		ptab->arg.flag = (ptab->arg.flag | HASH);
	else if (format[ptab->fmt] == '0')
		ptab->arg.flag = (ptab->arg.flag | ZERO);
	else if (format[ptab->fmt] == ' ')
		ptab->arg.flag = (ptab->arg.flag | SPACE);
	else if (format[ptab->fmt] == '.')
	{
		ptab->arg.flag = (ptab->arg.flag | PREC);
		get_size_flag(ptab, &format[ptab->fmt + 1], 1);
	}
	else
		return (0);
	return (1);
}

int				check_arg(const char *format, t_printf *ptab)
{
	int		mode;

	mode = 0;
	while (format[ptab->fmt])
	{
		if (mode == 0 && format[ptab->fmt] == '%' && ++ptab->fmt)
			mode = 1;
		if (mode == 0)
			fill_buffer(format[ptab->fmt++], ptab);
		else if (format[ptab->fmt] != '\0')
		{
			if (format[ptab->fmt] != '\0' && arg_flags(ptab, format))
				++ptab->fmt;
			else if (format[ptab->fmt] != '\0' && conv_flags(ptab, format))
				++ptab->fmt;
			else if (get_size_flag(ptab, &format[ptab->fmt], 0))
				++ptab->fmt;
			else if (arg_printf(ptab, format[ptab->fmt]))
				return (1);
		}
	}
	return (0);
}
