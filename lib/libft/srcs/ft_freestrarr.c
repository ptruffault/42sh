/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_freestrarr.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptruffau <ptruffau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/16 10:57:04 by ptruffau          #+#    #+#             */
/*   Updated: 2019/04/24 16:39:00 by fstadelw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

void	ft_freestrarr(char ***arr)
{
	size_t	i;

	if (!*arr || !**arr)
		return ;
	i = 0;
	while ((*arr)[i] != 0)
	{
		free((*arr)[i]);
		i++;
	}
	free(*arr);
	*arr = NULL;
}

char	**ft_delstrarr(char ***arr)
{
	ft_freestrarr(arr);
	return (NULL);
}
