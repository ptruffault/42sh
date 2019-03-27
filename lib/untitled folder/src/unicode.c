/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unicode.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stdenis <stdenis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/08 18:52:32 by stdenis           #+#    #+#             */
/*   Updated: 2019/03/15 18:10:12 by stdenis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <wchar.h>
#include "ft_printf.h"

static void	check_char_uni(uint32_t value, t_printf *ptab, size_t len)
{
	if (len == 1)
		fill_buffer(value, ptab);
	else if (len == 2)
	{
		fill_buffer(0xC0 | value >> 6, ptab);
		fill_buffer(0x80 | (value & 0x3f), ptab);
	}
	else if (len == 3)
	{
		fill_buffer(0xE0 | value >> 12, ptab);
		fill_buffer(0x80 | ((value >> 6) & 0x3f), ptab);
		fill_buffer(0x80 | (value & 0x3f), ptab);
	}
	else if (len == 4)
	{
		fill_buffer(0xF0 | value >> 18, ptab);
		fill_buffer(0x80 | ((value >> 12) & 0x3f), ptab);
		fill_buffer(0x80 | ((value >> 6) & 0x3f), ptab);
		fill_buffer(0x80 | (value & 0x3f), ptab);
	}
}

void		get_char_uni(va_list ap, void *ptr)
{
	t_printf	*ptab;
	char		fill;
	wchar_t		character;
	uint32_t	value;
	size_t		len;

	fill = ' ';
	ptab = (t_printf*)ptr;
	character = va_arg(ap, wchar_t);
	value = (uint32_t)character;
	if ((len = len_octects(character)) > 0)
	{
		ptab->arg.larg -= (ptab->arg.larg > 0) ? len : 0;
		if ((ptab->arg.flag & ZERO))
			fill = '0';
		while (!(ptab->arg.flag & MINUS) && ptab->arg.larg-- > 0)
			fill_buffer(fill, ptab);
		check_char_uni(value, ptab, len);
		while ((ptab->arg.flag & MINUS) && ptab->arg.larg-- > 0)
			fill_buffer(fill, ptab);
	}
}

void		while_wstr(wchar_t *str, t_printf *ptab, size_t len)
{
	size_t	i;
	size_t	len_o;

	i = -1;
	while (str[++i] && len > 0)
	{
		len_o = len_octects(str[i]);
		if (len >= len_o)
			check_char_uni(str[i], ptab, len_o);
		len -= (len_o > len) ? len : len_o;
	}
}

void		get_string_uni(va_list ap, void *ptr)
{
	t_printf	*ptab;
	char		fill;
	wchar_t		*string;
	int			len;

	ptab = (t_printf*)ptr;
	fill = ' ';
	string = va_arg(ap, wchar_t*);
	if (string == NULL)
		check_string(NULL, ptab);
	else
	{
		if ((ptab->arg.flag & ZERO))
			fill = '0';
		if ((len = ft_strlen_unicode(string, ptab)) >= 0)
		{
			if ((ptab->arg.flag & PREC) && ptab->arg.prec > 0)
				ptab->arg.larg -= (ptab->arg.larg > 0) ? len : 0;
			while (!(ptab->arg.flag & MINUS) && ptab->arg.larg-- > 0)
				fill_buffer(fill, ptab);
			while_wstr(string, ptab, len);
			while ((ptab->arg.flag & MINUS) && ptab->arg.larg-- > 0)
				fill_buffer(fill, ptab);
		}
	}
}
