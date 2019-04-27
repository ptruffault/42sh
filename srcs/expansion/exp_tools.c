/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp_tool.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptruffau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/22 19:07:48 by ptruffau          #+#    #+#             */
/*   Updated: 2019/04/22 19:07:49 by ptruffau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell42.h"

char	*ft_clear_quote(char *str)
{
	int i;

	i = -1;
	while (str && str[++i])
	{
		if (str[i] == '\'' || str[i] == '"')
		{
			while (str[i++])
				str[i - 1] = str[i];
			i = -1;
		}
	}
	return (str);
}

char	*ft_clear_backslash(char *str)
{
	int i;

	i = -1;
	while (str && str[++i])
	{
		if (str[i] == '\\' && ft_strchr("\\$", str[i + 1]))
		{
			while (str[i++])
				str[i - 1] = str[i];
			i++;
		}
	}
	return (str);
}
