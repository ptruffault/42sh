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
	int	start;

	start = *i;
	while (s && s[*i] && s[*i] == s[start])
		*i = *i + 1;
	return (ft_strsub(s, start, *i - start));
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

	if (val && pat && ft_str_endwith(val, pat))
	{
		new = ft_strndup(val, ft_strlen(val) - ft_strlen(pat));
		ft_strdel(&val);
		return (new);
	}
	return (val);
}

static char	*ft_cut_string(char *parenth, char *val, int *curr)
{
	char	*pattern;
	char	*tmp;
	char	*op;
	t_shell	*sh;

	sh = ft_get_set_shell(NULL);
	if ((op = ft_get_op(parenth, curr)))
	{
		if (parenth[*curr] && parenth[*curr] != '}'
		&& (pattern = ft_get_secondvalue(&parenth[*curr])))
		{
			*curr = *curr + ft_strlen(pattern) - 1;
			if (*pattern == '$' && (tmp = get_tenvv_val(sh->env, pattern + 1)))
			{
				ft_strdel(&pattern);
				pattern = ft_strdup(tmp);
			}
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
			ft_strdel(&pattern);
		}
		ft_strdel(&op);
	}
	return (val);
}

char		*ft_get_cutted_value(char *parenth, t_shell *sh, char *val, int *i)
{
	char *param;
	char *value;

	if (!val && parenth && (param = ft_get_secondvalue(parenth)))
	{
		if ((value = get_tenvv_val(sh->env, param))
		&& !(val = ft_strdup(value)))
		{
			ft_strdel(&param);
			return (NULL);
		}
		ft_strdel(&param);
	}
	return (ft_cut_string(parenth, val, i));
}
