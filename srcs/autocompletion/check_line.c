/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stdenis <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/18 15:33:46 by stdenis           #+#    #+#             */
/*   Updated: 2019/03/26 17:18:36 by stdenis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell42.h"

char	*get_word_cursor(char *str, int *pos)
{
	char	*ret;
	int		i;
	int		p;

	p = *pos;
	i = p;
	if (str[p] == ' ')
		p--;
	while (p > 0 && str[p] != ' ' && str[p] != ';')
		p--;
	p += (p > 0) ? 1 : 0;
	i = i - p;
	ret = ft_strndup(&str[p], i);
	p -= (p > 0) ? 1 : 0;
	while (p > 0 && str[p] == ' ')
		p--;
	p = (str[p] == ';') ? 0 : p;
	*pos = p;
	return (ret);
}

void	ft_arrdel(char ***arr)
{
	size_t	i;

	i = 0;
	while ((*arr)[i] != NULL)
	{
		free((*arr)[i]);
		i++;
	}
	free(*arr);
	*arr = NULL;
}


char	**get_tabl_others(char **path, char *value, int pos, int *total)
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
		tabl = get_binary(path, tmp, all, total);
		if (*total == 0)
			ft_arrdel(&tabl);
	}
	if (pos > 0 || *total == 0 || startwith)
		tabl = get_files(tmp, all, total);
	return (tabl);
}

char	**get_tabl_expansion(char *value, int *total)
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

char		**check_line(int *max_len, int *total, t_edit *e)
{
	char	*value;
	char	**path;
	char	**tabl;
	t_shell	*sh;
	int		pos;

	value = NULL;
	pos = e->curr;
	*total = 0;
	sh = ft_get_set_shell(NULL);
	if (!e->hist || !e->hist->s)
		return (NULL);
	if (!(value = get_word_cursor(e->hist->s, &pos)))
		return (NULL);
	if (!(path = ft_strsplit(get_tenvv_val(sh->env, "PATH"), ':')))
		return (NULL);
	if (value[0] != '$')
		tabl = get_tabl_others(path, value, pos, total);
	else
		tabl = get_tabl_expansion(value + 1, total);
	if (tabl != NULL && (*total <= 0))
		ft_arrdel(&tabl);
	else
		ft_sort_table(tabl, max_len);
	ft_freestrarr(&path);
	ft_strdel(&value);
	return (tabl);
}
