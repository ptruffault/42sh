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

int		ft_match_begin(const char *s, const char *p, t_bool mode)
{
	int i;
	int j;
	int len;

	i = 0;
	len = (int)ft_strlen(p);
	j = 0;
	while (s && s[i] && p && p[j] && (s[i] == p[j]
		|| (p[j] == '*' && (mode || p[j + 1]))))
	{
		if (p[j + 1] && p[j] == '*' && p[j + 1] == '*')
			while (p[j + 1] && p[j] == '*' && p[j + 1] == '*')
				j++;
		else if (p[j] != '*' && p[j] == s[i])
			j++;
		else if (p[j] == '*' && (p[j + 1] == s[i]))
			j = j + 2;
		i++;
	}
	if (j == len || (len > 0 && j == len - 1 && p[j] == '*'))
		return (i);
	return (0);
}

int		ft_match_end(const char *s, const char *p, t_bool mode)
{
	int i;
	int j;
	int len;

	len = (int)ft_strlen(p);
	i = (int)ft_strlen(s);
	j = len - 1;
	while (s && --i >= 0 && p && j >= 0 && s[i] && (s[i] == p[j]
		|| (p[j] == '*' && (mode || j > 0))))
	{
		if (j > 0 && p[j] == '*' && p[j - 1] == '*')
			while (j > 0 && p[j] == '*' && p[j - 1] == '*')
				j--;
		else if (p[j] != '*' && p[j] == s[i])
			j--;
		else if (p[j] == '*' && (j > 0 && p[j - 1] == s[i]))
			j = j - 2;
	}
	j = (j == -1) ? 0 : j;
	i = (i == -1) ? 0 : i;
	if (j == 0)
		return (i);
	return (-1);
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

char	*ft_clear_backslash(char *str)
{
	int i;

	i = -1;
	while (str && str[++i])
	{
		if (str[i] == '\\')
		{
			while (str[i++])
				str[i - 1] = str[i];
			i++;
		}
	}
	return (str);
}
