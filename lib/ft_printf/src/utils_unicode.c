/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_unicode.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stdenis <stdenis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/08 18:59:20 by stdenis           #+#    #+#             */
/*   Updated: 2019/03/11 16:27:15 by stdenis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <wchar.h>
#include "ft_printf.h"

size_t	ft_strlen_unicode(const wchar_t *str, t_printf *ptab)
{
	size_t	i;
	size_t	len;
	size_t	tmp;

	i = -1;
	len = 0;
	if (ptab->arg.flag & PREC)
		while (str[++i] != L'\0')
		{
			if ((tmp = len_octects(str[i])) == 5)
				return (-1);
			if (tmp + len > (size_t)ptab->arg.prec)
				return (len);
			else
				len += tmp;
		}
	else
		while (str[++i] != L'\0')
		{
			if ((tmp = len_octects(str[i])) == 5)
				return (-1);
			else
				len += tmp;
		}
	return (len);
}

size_t	len_octects(const wchar_t c)
{
	uint32_t	val;
	size_t		len;

	val = (uint32_t)c;
	len = 0;
	if (val >= 0xd800 && val <= 0xdfff)
		return (5);
	else if (val <= 0x7F)
		return (len = 1);
	else if (val <= 0x7FF)
		return (len = 2);
	else if (val <= 0xFFFF)
		return (len = 3);
	else if (val <= 0x10FFFF)
		return (len = 4);
	return (len);
}
