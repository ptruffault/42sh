/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cut_glob.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptruffau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/25 15:48:34 by ptruffau          #+#    #+#             */
/*   Updated: 2019/04/25 15:48:35 by ptruffau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell42.h"

static char	*ft_cut_glob_begin(char *val, char *pat, char *op)
{
	char	*new;
	int		len;

	if ((len = ft_match_begin(val, pat, *op == op[1] ? TRUE : FALSE)) > 0)
	{
		new = ft_strdup(val + len);
		ft_strdel(&val);
		return (new);
	}
	return (val);
}

static char	*ft_cut_glob_end(char *val, char *pat, char *op)
{
	char	*new;
	int		len;

	if ((len = ft_match_end(val, pat, *op == op[1] ? TRUE : FALSE)) >= 0)
	{
		new = ft_strndup(val, len);
		ft_strdel(&val);
		return (new);
	}
	return (val);
}

char		*ft_cut_glob(char *val, char *pattern, char *op)
{
	if (*op == '#')
		val = ft_cut_glob_begin(val, pattern, op);
	else if (*op == '%')
		val = ft_cut_glob_end(val, pattern, op);
	if (ft_strequ(op, "##"))
		while (ft_match_begin(val, pattern, TRUE) > 0)
			val = ft_cut_glob_begin(val, pattern, op);
	else if (ft_strequ(op, "%%"))
		while (ft_match_end(val, pattern, TRUE) > 0)
			val = ft_cut_glob_end(val, pattern, op);
	return (val);
}
