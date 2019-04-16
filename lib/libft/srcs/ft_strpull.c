/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strpull.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptruffau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/21 14:15:39 by ptruffau          #+#    #+#             */
/*   Updated: 2018/06/21 14:15:41 by ptruffau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

char	*ft_strpull(char *src, char *ptr, int len, char *value)
{
	if (src && ptr)
	{
		if (src - ptr == 0)
			return (ft_strjoin(value, src + len + 1));
		return (ft_strjoin_fr(ft_strndup(src, ptr - src),
					ft_strjoin(value, ptr + len + 1)));
	}
	return (NULL);
}

char	*ft_strpull_exp(char *src, char *ptr, int len, char *value)
{
	if (src && ptr)
	{
		if (src - ptr == 0)
		{
			if (ft_strlen(value) == 0)
				return (ft_strndup(src + len + 1, ft_strlen(src + len + 1)));
			else
				return (ft_strjoin(value, src + len + 1));
		}
		if (ft_strlen(value) == 0)
			return (ft_strjoin_fr(ft_strndup(src, ptr - src),
					ft_strdup(ptr + len + 1)));
		else
			return (ft_strjoin_fr(ft_strndup(src, ptr - src),
		ft_strjoin(value, ptr + len + 1)));
	}
	return (NULL);
}
