/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stdenis <stdenis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/18 15:33:46 by stdenis           #+#    #+#             */
/*   Updated: 2019/04/24 17:07:00 by fstadelw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "shell42.h"
#include "ft_printf.h"

static char	*get_word_cursor(char *str, int *pos)
{
	char	*ret;
	int		i;
	int		p;

	p = *pos;
	i = p;
	if (str[p] == ' ')
		p--;
	while (p > 0 && ((str[p] != ' ' && str[p] != ';'
			&& str[p] != '|' && str[p] != '&'
			&& str[p] != '"' && str[p] != '\'')
			|| ((str[p] =='"' || str[p] == '\'') && str[p - 1] == '\\')))
		p--;
	p += (p > 0) ? 1 : 0;
	i = i - p;
	if (p > 0 && str[p] == '\\')
		p++;
	ret = ft_strndup(&str[p], i);
	p -= (p > 0) ? 1 : 0;
	while (p > 0 && str[p] == ' ')
		p--;
	if (p > 0)
		p = (ft_strchr("|&;", str[p]) && str[p - 1] != '\\') ? 0 : p;
	*pos = p;
	return (ret);
}

static char	**get_tabl_others(char *value, int pos, int *total)
{
	char	**tabl;
	char	*tmp;
	bool	all;
	bool	startwith;

	tabl = NULL;
	startwith = (ft_str_startwith(value, "./")) ? true : false;
	tmp = (startwith) ? value + 2 : value;
	all = (ft_strlen(tmp) == 0) ? true : false;
	if (pos == 0 && !startwith)
	{
		tabl = get_binary(ft_get_set_shell(NULL), tmp, all, total);
		if (*total == 0)
			ft_arrdel(&tabl);
	}
	if (pos > 0 || *total == 0 || startwith)
		tabl = get_files(tmp, all, total);
	return (tabl);
}

static char	**get_tabl_expansion(char *value, int *total)
{
	char	**tabl;
	bool	all;

	tabl = NULL;
	all = false;
	if (value[0] == '{')
		value += 1;
	if (value[0] == '\0')
		all = true;
	tabl = get_environ_match(value, total, all);
	return (tabl);
}

char		**only_tilde(int *max_len, int *total, char *str)
{
	char	**res;

	if (!(res = malloc(sizeof(char*) * 2)))
		return (NULL);
	res[1] = NULL;
	if (!(res[0] = check_tilde(str)))
	{
		ft_arrdel(&res);
		return (NULL);
	}
	*total = 1;
	*max_len = (int)ft_strlen(res[0]);
	return (res);
}

char		**check_line(int *max_len, int *total, t_edit *e)
{
	char	*value;
	char	**tabl;
	int		pos;

	value = NULL;
	pos = (int)e->curr;
	*total = 0;
	if (!e->hist || !e->hist->s
		|| !(value = get_word_cursor(e->hist->s, &pos)))
		return (NULL);
	pos = check_before(e->hist->s, pos);
	if (ft_strequ(value, "~"))
		return (only_tilde(max_len, total, value));
	if (!(value = check_tilde(value)))
		return (NULL);
	if (value[0] != '$')
		tabl = get_tabl_others(value, pos, total);
	else
		tabl = get_tabl_expansion(value + 1, total);
	if (tabl != NULL && (*total <= 0))
		ft_arrdel(&tabl);
	else if (tabl != NULL)
		ft_sort_table(tabl, max_len);
	ft_strdel(&value);
	return (tabl);
}
