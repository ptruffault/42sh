/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptruffau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/16 13:19:06 by ptruffau          #+#    #+#             */
/*   Updated: 2019/03/26 16:47:28 by stdenis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_stradd(char **str, const char *end)
{
	char	*rtn;

	rtn = ft_strjoin(*str, end);
	ft_strdel(str);
	*str = rtn;
	return (rtn);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char				*ret;
	unsigned int		count;

	count = 0;
	if (s1 && (!s2 || *s2 == 0))
		return (ft_strdup(s1));
	if ((!s1 || *s1 == 0) && s2)
		return (ft_strdup(s2));
	if ((!s1 && !s2) || !(ret = ft_strnew(ft_strlen(s1) + ft_strlen(s2))))
		return (NULL);
	while (*s1)
	{
		*ret++ = *s1++;
		count++;
	}
	while (*s2)
	{
		*ret++ = *s2++;
		count++;
	}
	*ret = '\0';
	return (ret - count);
}
