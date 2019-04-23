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

int		ft_match_begin(const char *s, const char *p, t_bool end)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (s && s[i] && p && p[j] && (s[i] == p[j] 
		|| (p[j] == '*' && (end || p[j + 1]))))
	{
		if (p[j] != '*' && p[j] == s[i])
			j++;
		else if (p[j] == '*' && (p[j + 1] == s[i]))
			j = j + 2;
		i++;
	}
	return (i);
}
int		ft_match_end(const char *s, const char *p, t_bool end)
{
	int i;
	int j;

	i = (int)ft_strlen(s) - 1;
	j = (int)ft_strlen(p) - 1;
	while (s && i >= 0 && p && j >= 0 && (s[i] == p[j] 
		|| (p[j] == '*' && (end || j > 0))))
	{
		if (p[j] != '*' && p[j] == s[i])
			j--;
		else if (p[j] == '*' && (p[j - 1] == s[i]))
		{
			j++;
			j = (p[j + 1] ? j++ : j);
		}
		i--;
	}
	return (i + 1);
}

char	*ft_clear_glob(char *str)
{
	int i;

	i = -1;
	while (str && str[++i])
	{
		if (str[i] == '*')
		{
			while (str[i++])
				str[i - 1] = str[i];
			i = -1;
		}
	}
	return (str);
}


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
