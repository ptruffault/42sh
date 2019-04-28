/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp_parenth.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adi-rosa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/18 15:26:29 by adi-rosa          #+#    #+#             */
/*   Updated: 2019/03/26 17:21:55 by stdenis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell42.h"

static char	*ft_exp_end(char *ret, char *ptr, char *value, char *parenth)
{
	char *tmp;

	tmp = NULL;
	if (value && ft_isempty(value))
		ft_strdel(&value);
	if (value && ret && ptr
		&& (tmp = ft_strpull(ret, ptr, get_cnt_size(ptr) + 2, value))
		&& ft_isempty(tmp))
		ft_strdel(&tmp);
	ft_strdel(&ret);
	ft_strdel(&value);
	ft_strdel(&parenth);
	return (tmp);
}

static char	*ft_error(char *v1, char *v2, t_shell *sh)
{
	v2 = ft_exp_var(v2, sh, TRUE);
	error(v1, v2);
	sh->exp_leave = 1;
	sh->env = ft_new_envv_int(sh->env, "?", 1, IN);
	return (v2);
}

static char	*handle_modifier(char *parenth, char *o, t_shell *sh, char *param)
{
	char *val;
	char *v1;
	char *v2;

	val = NULL;
	v2 = NULL;
	if (parenth && (v1 = ft_strndup(parenth, (int)(o - parenth - 1)))
		&& (v2 = ft_strdup(param)))
	{
		if ((*o == '-' && !(get_tenvv(sh->env, v1)))
			|| (*o == '+' && get_tenvv(sh->env, v1)))
			val = ft_strdup(v2);
		else if (v2 && *o == '=' && !(get_tenvv(sh->env, v1)))
		{
			v2 = ft_exp_var(v2, sh, TRUE);
			val = ft_strdup(v2);
			sh->env = ft_new_envv(sh->env, v1, v2, IN);
		}
		else if (v2 && *o == '?' && !(get_tenvv(sh->env, v1)))
			v2 = ft_error(v1, v2, sh);
		val = val ? val : ft_strdup(get_tenvv_val(sh->env, v1));
		ft_strdel(&v1);
		ft_strdel(&v2);
	}
	return (val);
}

static char	*ft_get_param_value(t_shell *sh, char *parenth)
{
	int		i;
	char	*val;
	char	*param;

	i = -1;
	val = NULL;
	while (parenth && (i + 1 < (int)ft_strlen(parenth)) && parenth[++i])
		if (parenth[i] == ':' && parenth[i + 1] != '\0'
			&& ft_strchr("-+?=", parenth[i + 1])
			&& (param = ft_get_secondvalue(&parenth[i + 2])))
		{
			ft_strdel(&val);
			val = handle_modifier(parenth, &parenth[i + 1], sh, param);
			ft_strdel(&param);
			i += (int)ft_strlen(param);
		}
		else if (parenth[i] == '#' || parenth[i] == '%')
			val = ft_get_cutted_value(parenth, sh, val, &i);
	if (!val && !(val = ft_strdup(get_tenvv_val(sh->env, parenth))))
		return (NULL);
	return (val);
}

char		*ft_exp_param(char *ret, char *ptr, t_shell *sh)
{
	char	*value;
	char	*parth;
	int		len;

	value = NULL;
	parth = ft_strsub(ret, (t_opts)(ptr - ret + 2), (size_t)get_cnt_size(ptr));
	if (!parth || *parth == '$' || ft_isempty(parth)
		|| *parth == '"' || *parth == '\'')
	{
		ft_strdel(&parth);
		warning("bad substitution", ret);
		ft_strdel(&ret);
		return (NULL);
	}
	len = (*parth == '#' ? 1 : 0);
	value = ft_get_param_value(sh, &parth[len]);
	value = (len == 1 ? ft_get_len(value) : value);
	return (ft_exp_end(ret, ptr, value, parth));
}
