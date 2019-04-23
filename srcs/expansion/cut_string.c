/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adi-rosa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/18 14:05:53 by adi-rosa          #+#    #+#             */
/*   Updated: 2019/03/26 17:21:55 by stdenis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell42.h"

static char	*ft_get_op(char *s, int *i)
{
	unsigned int start;

	start = (unsigned int)*i;
	while (s && s[*i] && s[*i] == s[start])
		*i = *i + 1;
	return (ft_strsub(s, start, (size_t)*i - start));
}

static char *ft_cut_glob(char *val, char *pat, char *op)
{
	char *tmp;
	char *new;

	if ((tmp = ft_strstr(val, ft_clear_glob(pat))))
	{
		if (*op == '#')
		{
			new = ft_strndup(val, tmp - val);
			ft_strdel(&val);
			return (new);
		}
		else if (*op == '%')
		{
			new = ft_strndup(val, tmp - val);
			ft_strdel(&val);
			return (new);
		}
	}
	return (val);
}

static char	*ft_cut_begin(char *val, char *pat)
{
	char	*new;
	char	*tmp;

	new = NULL;
	if (val && pat && ft_str_startwith(val, pat))
	{
		if ((tmp = val + ft_strlen(pat))
		&& !(new = ft_strdup(tmp)))
			return (ft_strdell(&val));
		ft_strdel(&val);
		return (new);
	}
	return (val);
}

static char	*ft_cut_end(char *val, char *pat)
{
	char	*new;
	size_t	len;
	
	if (val && pat && ft_str_endwith(val, pat))
	{
		len = ft_strlen(val) - ft_strlen(pat);
		new = ft_strndup(val, (int)len);
		ft_strdel(&val);
		return (new);
	}
	return (val);
}

static char	*ft_handle_op(char *op, char *val, char *pattern)
{
	if (!pattern)
		return (val);
	if (ft_strchr(pattern, '*'))
		return (ft_cut_glob(val, pattern, op));
	if (ft_strequ(op, "##"))
		while (val && ft_str_startwith(val, pattern))
			val = ft_cut_begin(val, pattern);
	else if (ft_strequ(op, "%%"))
		while (val && *val && ft_str_endwith(val, pattern))
			val = ft_cut_end(val, pattern);
	else if (*op == '#')
		val = ft_cut_begin(val, pattern);
	else if (*op == '%')
		val = ft_cut_end(val, pattern);
	return (val);
}

char		*ft_cut_string(char *parenth, char *val, int *curr)
{
	char	*pattern;
	char	*op;
	t_shell	*sh;

	sh = ft_get_set_shell(NULL);
	if ((op = ft_get_op(parenth, curr)))
	{
		if (parenth[*curr] && parenth[*curr] != '}'
		&& (pattern = ft_get_secondvalue(&parenth[*curr])))
		{
			// to change for '*' 
			*curr = *curr + (int)ft_strlen(pattern) - 1;
			pattern = ft_exp_var(pattern, sh, TRUE);
			val = ft_handle_op(op, val, pattern);
			ft_strdel(&pattern);
		}
		ft_strdel(&op);
	}
	return (val);
}
