/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   31usr2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fstadelw <fstadelw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/18 00:30:12 by fstadelw          #+#    #+#             */
/*   Updated: 2018/12/18 00:43:51 by fstadelw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>

int	main(void)
{
	raise(SIGUSR2);
	return (0);
}
