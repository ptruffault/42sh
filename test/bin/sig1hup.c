/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1hup.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fstadelw <fstadelw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/18 00:30:12 by fstadelw          #+#    #+#             */
/*   Updated: 2018/12/18 00:40:46 by fstadelw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>

int	main(void)
{
	raise(SIGHUP);
	return (0);
}
