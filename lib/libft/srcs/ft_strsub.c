/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptruffau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/16 13:27:14 by ptruffau          #+#    #+#             */
/*   Updated: 2017/12/03 16:11:05 by ptruffau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

char	*ft_strsub(char const *s, unsigned int start, size_t len)
{
	char	*new;
	size_t	i;

	if (!s || len == 0)
		return (NULL);
	if (!(new = ft_strnew(len)))
		return (NULL);
	i = 0;
	while (i < len && s[start])
		new[i++] = s[start++];
	return (new);
}
