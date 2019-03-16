/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_freestrarr.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptruffau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/16 10:57:04 by ptruffau          #+#    #+#             */
/*   Updated: 2017/11/16 11:11:47 by ptruffau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

char 	**ft_freestrarr(char **arr)
{
	int i;

	i = 0;
	if (arr && *arr)
	{
		while (arr[i])
			ft_strdel(&arr[i++]);
		free(arr);
	}
	return (NULL);
}
