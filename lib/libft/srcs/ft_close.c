/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_close.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adi-rosa <adi-rosa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/05 13:03:55 by adi-rosa          #+#    #+#             */
/*   Updated: 2019/04/24 16:38:15 by fstadelw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "libft.h"

int	ft_close(int fd)
{
	char *n;

	if (fd >= 0 && close(fd) == -1)
	{
		n = ft_itoa(fd);
		warning("close failure fd ->", n);
		ft_strdel(&n);
		return (0);
	}
	return (1);
}
