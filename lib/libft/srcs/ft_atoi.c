/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adi-rosa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/07 09:07:20 by adi-rosa          #+#    #+#             */
/*   Updated: 2017/11/30 13:00:10 by adi-rosa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *str)
{
	int				i;
	unsigned int	nb;
	int				neg;

	i = 0;
	nb = 0;
	neg = 0;
	while ((str[i] == ' ') || (str[i] == '\t') || (str[i] == '\n')
			|| (str[i] == '\v') || (str[i] == '\f') || (str[i] == '\r'))
		++i;
	if (str[i] == '-')
		neg = 1;
	if (str[i] == '-' || str[i] == '+')
		++i;
	while (str[i] && str[i] >= '0' && str[i] <= '9')
		nb = nb * 10 + (str[i++] - '0');
	if ((nb > 2147483647 && neg == 0)
		|| (nb > 2147483648 && neg == 1))
		return (nb > 2147483648 && neg == 1 ? 0 : -1);
	return ((int)neg == 1 ? -nb : nb);
}
