/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup_parse.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptruffau <ptruffau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/08 16:18:28 by ptruffau          #+#    #+#             */
/*   Updated: 2019/04/24 16:43:03 by fstadelw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t		count_char_spec(const char *str)
{
	size_t	count;
	int		i;

	count = 0;
	i = -1;
	while (str[++i])
	{
		if (ft_strchr(" \\\'\"", str[i]))
			count++;
	}
	return (count);
}

char		*ft_strdup_parse(const char *str)
{
	char	*ret;
	size_t	len;
	size_t	count;
	int		i;
	int		j;

	i = -1;
	j = 0;
	len = ft_strlen(str);
	count = count_char_spec(str);
	if (!(ret = ft_strnew(len + count)))
		return (NULL);
	while (str[++i])
	{
		if (ft_strchr(" \\'\"", str[i]))
			ret[j++] = '\\';
		ret[j] = str[i];
		j++;
	}
	return (ret);
}
