/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_add.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stdenis <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/18 15:33:46 by stdenis           #+#    #+#             */
/*   Updated: 2019/03/26 17:18:36 by stdenis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin_add_edit(char **s1, const char *add, int err)
{
	char	*tmp;

	tmp = *s1;
	if (tmp && ((err <= 3 || err > 5)
		|| (err == 4 && tmp[ft_strlen(tmp) - 1] != '\\')))
	{
		if (!(*s1 = ft_stradd(s1, add)))
			return (NULL);
	}
	else if (tmp && tmp[ft_strlen(tmp) - 1] == '\\')
		tmp[ft_strlen(tmp) - 1] = '\0';
	return (*s1);
}

char	*ft_strjoin_add_if(char **s1, char **s2, const char *add)
{
	char	*ret;
	char	*tmp;

	tmp = *s1;
	if (tmp && tmp[ft_strlen(tmp) - 1] != '\\')
	{
		if (!(*s1 = ft_stradd(s1, add)))
		{
			ft_strdel(s2);
			return (NULL);
		}
	}
	else if (tmp)
		tmp[ft_strlen(tmp) - 1] = '\0';
	ret = ft_strjoin(*s1, *s2);
	ft_strdel(s1);
	ft_strdel(s2);
	return (ret);
}

char	*ft_strjoin_add(char **s1, char **s2, const char *add)
{
	char	*ret;

	if (!(*s1 = ft_stradd(s1, add)))
	{
		ft_strdel(s2);
		return (NULL);
	}
	ret = ft_strjoin(*s1, *s2);
	ft_strdel(s1);
	ft_strdel(s2);
	return (ret);
}
