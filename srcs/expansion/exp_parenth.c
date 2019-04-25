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
		&& (tmp = ft_strpull(ret, ptr, get_content_size(ptr) + 2, value))
		&& ft_isempty(tmp))
		ft_strdel(&tmp);
	ft_strdel(&ret);
	ft_strdel(&value);
	ft_strdel(&parenth);
	return (tmp);
}

static char	*ft_get_len(char *value)
{
	char *tmp;

	tmp = ft_itoa((int)ft_strlen(value));
	ft_strdel(&value);
	return (tmp);
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
		else if (v2 && *o == '?' && !(get_tenvv(sh->env, v1)) && error(v1, v2))
			v2 = ft_exp_var(v2, sh, TRUE);
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
	while (parenth && parenth[++i])
		if (parenth[i] == ':' && ft_strchr("-+?=", parenth[i + 1])
			&& parenth[i + 1] != '\0'
			&& (param = ft_get_secondvalue(&parenth[i + 2])))
		{
			ft_strdel(&val);
			val = handle_modifier(parenth, &parenth[i + 1], sh, param);
			i = i + (int)ft_strlen(param);
			ft_strdel(&param);
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
	char	*parenth;
	int		len;

	value = NULL;
	parenth = ft_strsub(ret, (unsigned int)(ptr - ret + 2),
	(size_t)get_content_size(ptr));
	if (!parenth || *parenth == '$' || ft_isempty(parenth)
		|| *parenth == '"' || *parenth == '\'')
	{
		ft_strdel(&parenth);
		warning("bad substitution", ret);
		ft_strdel(&ret);
		return (NULL);
	}
	len = (*parenth == '#' ? 1 : 0);
	value = ft_get_param_value(sh, &parenth[len]);
	value = (len == 1 ? ft_get_len(value) : value);
	return (ft_exp_end(ret, ptr, value, parenth));
}
