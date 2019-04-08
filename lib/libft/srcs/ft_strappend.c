/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strappend.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stdenis <stdenis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/10 10:52:45 by stdenis           #+#    #+#             */
/*   Updated: 2019/01/28 20:32:02 by stdenis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_strlen_trim(char *value)
{
	size_t	i;
	size_t	count;

	i = 0;
	count = 0;
	while (value[i])
	{
		if (value[i] >= 9 && value[i] <= 13)
			i++;
		else
		{
			i++;
			count++;
		}
	}
	return (count);
}

char			*ft_strappend_fr(char **str, char **end)
{
	char	*rtn;

	rtn = ft_strjoin(*str, *end);
	ft_strdel(str);
	ft_strdel(end);
	*str = rtn;
	return (rtn);
}

char			*ft_strappend(char **str, const char *end)
{
	char	*rtn;

	rtn = ft_strjoin(*str, end);
	ft_strdel(str);
	*str = rtn;
	return (rtn);
}

char			*ft_strdup_trim(char *value)
{
	size_t	i;
	size_t	j;
	size_t	len;
	char	*ret;

	i = 0;
	j = 0;
	len = ft_strlen_trim(value);
	if (!(ret = ft_strnew(len)))
		return (NULL);
	while (value[i])
	{
		if (value[i] >= 9 && value[i] <= 13)
			i++;
		else
		{
			ret[j] = value[i++];
			j++;
		}
	}
	return (ret);
}
