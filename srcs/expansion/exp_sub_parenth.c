/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp_sub_parenth.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptruffau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/08 15:57:04 by ptruffau          #+#    #+#             */
/*   Updated: 2019/03/26 17:21:55 by stdenis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell42.h"


static char	*sub_handle_modifier(char *parenth, char *ptr, t_shell *sh)
{
	char *val;
	char *val1;
	char *val2;

	val = NULL;
	if (parenth && (val1 = ft_strndup(parenth, ptr - parenth - 1)))
	{
		val2 = ptr + 1;
		if ((*ptr == '-' && !(get_tenvv(sh->env, val1)))
		|| (*ptr == '+' && get_tenvv(sh->env, val1))
		|| (*ptr == '=' && !(get_tenvv(sh->env, val1))
		&& (sh->env = ft_new_envv(sh->env, val1, val2, true))))
			val = val2;
		else if (*ptr == '?' && !(get_tenvv(sh->env, val1)))
			error(val1, val2);
		ft_strdel(&val1);
	}
	return (ft_strdup(val));
}

static char	*sub_get_param_value(char *old_parenth, t_shell *sh)
{
	char *parenth;
	char *value;
	char *ptr;

	if (!(parenth = ft_strsub(old_parenth, 2, get_content_size(old_parenth))))
		return (NULL);
	value = NULL;
	if (ft_str_startwith(parenth, "${"))
		parenth = sub_get_param_value(parenth, sh);
	if ((ptr = ft_strchr(parenth, ':')) && ++ptr)
	{
		if (ft_strchr("-+?=", *ptr))
			value = sub_handle_modifier(parenth, ptr, sh);
		else
		{
			error_c("unrecognized modifier", *ptr);
			return (NULL);
		}
	}
	else
		value = ft_strdup(parenth);
	ft_strdel(&parenth);
	ptr = ft_strpull(old_parenth, old_parenth,
	get_content_size(old_parenth) + 3, value);
	return (ptr);
}

char		*ft_exp_param_sub(char *parenth, t_shell *sh)
{
	char *tmp;

	while (ft_str_startwith(parenth, "${")
	&& (tmp = sub_get_param_value(parenth, sh)))
	{
		ft_strdel(&parenth);
		parenth = tmp;
	}
	return (parenth);
}
