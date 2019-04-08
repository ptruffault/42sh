/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_freestrarr.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptruffau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/16 10:57:04 by ptruffau          #+#    #+#             */
/*   Updated: 2019/03/19 18:39:15 by stdenis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

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

char	*ft_delstrarr(char ***arr)
{
	ft_freestrarr(arr);
	return (NULL);
}