/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stdenis <stdenis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/25 13:34:03 by stdenis           #+#    #+#             */
/*   Updated: 2019/03/08 19:55:19 by stdenis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	fill_with_string(char *value, t_printf *ptab, size_t len, char fill)
{
	size_t		i;

	i = -1;
	while (!(ptab->arg.flag & MINUS) && ptab->arg.larg-- > 0)
		fill_buffer(fill, ptab);
	while (value[++i] && len-- > 0)
		fill_buffer(value[i], ptab);
	while ((ptab->arg.flag & MINUS) && ptab->arg.larg-- > 0)
		fill_buffer(fill, ptab);
}

void		check_string(char *value, t_printf *ptab)
{
	size_t		len;

	if (value == NULL)
	{
		len = (ptab->arg.flag & PREC) ? ptab->arg.prec : 6;
		ptab->arg.larg -= (ptab->arg.larg > 0) ? len : 0;
		if (ptab->arg.flag & ZERO && !(ptab->arg.flag & MINUS))
			fill_with_string("(null)", ptab, len, '0');
		else
			fill_with_string("(null)", ptab, len, ' ');
	}
	else
	{
		len = ft_strlen(value);
		if (ptab->arg.flag & PREC && ptab->arg.type == S)
			len = ((int)len < ptab->arg.prec) ? len : (size_t)ptab->arg.prec;
		ptab->arg.larg -= (ptab->arg.larg > 0) ? len : 0;
		if (ptab->arg.flag & ZERO && !(ptab->arg.flag & MINUS))
			fill_with_string(value, ptab, len, '0');
		else
			fill_with_string(value, ptab, len, ' ');
	}
}

void		get_string(va_list ap, void *ptr)
{
	t_printf *tab;

	tab = (t_printf*)ptr;
	check_string(va_arg(ap, char *), tab);
}
