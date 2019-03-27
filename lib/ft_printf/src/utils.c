/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stdenis <stdenis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/22 13:58:57 by stdenis           #+#    #+#             */
/*   Updated: 2019/03/11 18:30:10 by stdenis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		get_size_flag(t_printf *ptab, const char *str, int prec)
{
	int		i;
	int		value;

	i = 0;
	value = 0;
	while (*str && (str[i] >= '0' && str[i] <= '9'))
	{
		value = 10 * value + (str[i] - '0');
		i++;
	}
	if (i > 0 || (ptab->arg.prec > 0 && prec == 1))
	{
		if (prec == 1)
		{
			ptab->fmt += i;
			ptab->arg.prec = value;
		}
		else
		{
			ptab->arg.larg = value;
			ptab->fmt += i - 1;
		}
		return (1);
	}
	return (0);
}

int		int_length(intmax_t value, int base)
{
	size_t	i;

	i = 0;
	if (value < 0)
	{
		value++;
		value *= -1;
	}
	while (value > 0)
	{
		i++;
		value /= base;
	}
	return ((i == 0) ? 1 : i);
}

void	*ft_memset(void *b, int c, size_t n)
{
	size_t			i;

	i = -1;
	while (++i < n)
		((unsigned char*)b)[i] = c;
	return (b);
}

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i] != '\0')
	{
		i++;
	}
	return (i);
}

void	rounding_prec_zero(t_dbl *tab_dbl, t_printf *ptab)
{
	size_t	len;
	int		last;

	last = 0;
	tab_dbl->before_dot++;
	if (*tab_dbl->before_dot > 0)
	{
		len = int_length(*tab_dbl->before_dot, 10);
		if (len >= 9 && *tab_dbl->before_dot % 100000000 != 0)
		{
			while (len-- > 1)
				*tab_dbl->before_dot /= 10;
			if (*tab_dbl->before_dot >= 5)
			{
				last = ptab->buffer[ptab->buff - 1] - '0' + 1;
				ptab->buffer[ptab->buff - 1] = last + '0';
			}
		}
	}
}
