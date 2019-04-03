/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parenth_tools.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptruffau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/18 15:43:53 by ptruffau          #+#    #+#             */
/*   Updated: 2019/03/26 17:21:55 by stdenis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell42.h"

char		*ft_get_secondvalue(char *src)
{
	char	*cpy;
	char	*ret;
	int		i;

	i = 0;
	ret = NULL;
	if (src && (cpy = ft_strdup(src)))
	{
		while (cpy && cpy[i] && cpy[i] != '#' && cpy[i] != '%' &&
		(i == 0 || cpy[i - 1] != '}'))
			i++;
		if (cpy && !(ret = ft_strndup(cpy, i)))
			return (ft_strdell(&cpy));
		ft_strdel(&cpy);
	}
	return (ret);
}

int	get_content_size(char *s)
{
	int i;

	i = 2;
	if (!s)
		return (0);
	while (s[i] && s[i] != '}')
	{
		if (s[i] == '$' && s[i + 1] == '{')
			i = i + get_content_size(&s[i]) + 2;
		i++;
	}
	return (i - 2);
}
