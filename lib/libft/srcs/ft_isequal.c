/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adi-rosa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/05 13:19:37 by adi-rosa          #+#    #+#             */
/*   Updated: 2019/02/05 13:20:53 by adi-rosa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isequal_env(char *s)
{
	char *ptr;

	if (s && *s != '=' && (ptr = ft_strchr(s, '=')))
		return (1);
	return (0);
}

int	ft_isequal(char *s)
{
	char *ptr;

	if (s && *s != '=' && (ptr = ft_strchr(s, '=')) && ptr + 1 != 0)
		return (1);
	return (0);
}
