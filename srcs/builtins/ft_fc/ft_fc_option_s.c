/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fc_option_s.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adi-rosa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/01 16:07:49 by adi-rosa          #+#    #+#             */
/*   Updated: 2019/04/01 16:07:50 by adi-rosa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell42.h"

static char		*repl_occ(char *old, char *new, char *str)
{
	size_t	x;
	char	*tmp;
	size_t	old_size;
	size_t	new_size;

	new_size = ft_strlen(new);
	old_size = ft_strlen(old);
	tmp = NULL;
	x = 0;
	if (!str)
		return (NULL);
	while (str[x])
	{
		if (ft_str_startwith(str + x, old))
		{
			if (!(tmp = ft_strpull(str, str + x, (int)old_size - 1, new)))
				return (NULL);
			ft_strdel(&str);
			str = tmp;
			x += new_size;
		}
		else
			++x;
	}
	return (str);
}

static int		ft_fc_fill_pos(t_fc *fc, int pos)
{
	if (fc->av[pos + 1])
	{
		if (ft_isdigit(fc->av[pos + 1][0]) || fc->av[pos + 1][0] == '-')
		{
			fc->first = ft_atoi(fc->av[pos + 1]);
			fc->first = (fc->first == 0) ? -1 : fc->first;
		}
		else
			fc->first_ = fc->av[pos + 1];
	}
	if (search_in_hist_parser(fc, 1) == FAILURE)
		return (FAILURE);
	return (SUCCESS);
}

static t_hist	*ft_fc_option_s_replace(t_fc *fc, int pos)
{
	char	**tabl;
	t_hist	*hist;
	char	*tmp;

	if (!(tabl = ft_strsplit(fc->av[pos], '='))
		|| (!tabl[0] || (tabl[0] && !tabl[1])))
	{
		ft_freestrarr(&tabl);
		return (NULL);
	}
	if (ft_fc_fill_pos(fc, pos) == FAILURE)
	{
		ft_freestrarr(&tabl);
		return (NULL);
	}
	hist = fc->shell->hist;
	if (!(tmp = repl_occ(tabl[0], tabl[1], ft_strdup(fc->hist_first->s))))
	{
		ft_freestrarr(&tabl);
		return (NULL);
	}
	ft_strdel(&hist->s);
	ft_freestrarr(&tabl);
	hist->s = tmp;
	return (hist);
}

void			ft_fc_option_s(t_fc *fc, int pos)
{
	t_tree	*t;
	t_hist	*hist;

	hist = NULL;
	if (fc->av[pos] && ft_strchr(fc->av[pos], '=')
		&& !(hist = ft_fc_option_s_replace(fc, pos)))
		return ;
	else if (hist == NULL)
	{
		if (search_in_hist_parser(fc, 1) == FAILURE)
			return ;
		hist = fc->shell->hist;
		ft_strdel(&hist->s);
		if (!(hist->s = ft_strdup(fc->hist_first->s)))
			return ;
	}
	fc->shell->fc = TRUE;
	fc->shell->interactive = FALSE;
	if ((t = get_tree(hist->s, ft_get_set_shell(NULL))))
		ft_free_tree(exec_tree(t, fc->shell));
	fc->shell->fc = FALSE;
	fc->shell->interactive = TRUE;
}
