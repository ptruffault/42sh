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

char			*replace_occurances(char *old, char *new, char *str)
{
	size_t	x;
	char	*tmp;
	size_t	old_size;
	size_t	new_size;

	new_size = ft_strlen(new);
	old_size = ft_strlen(old);
	tmp = NULL;
	x = 0;
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

static t_hist	*ft_fc_option_s_replace(t_fc *fc, int pos)
{
	char	**tabl;
	t_hist	*hist;
	char	*tmp;

	if (!(tabl = ft_strsplit(fc->av[pos], '='))
			|| (!tabl[0] || (tabl[0] && !tabl[1])))
		return (NULL);
	if (fc->av[pos + 1])
	{
		if ((fc->av[pos + 1][0] >= '0' && fc->av[pos + 1][0] <= '9')
			|| fc->av[pos + 1][0] == '-')
			fc->first = ft_atoi(fc->av[pos + 1]) == 0 ? -1
				: ft_atoi(fc->av[pos + 1]);
		else
			fc->first_ = fc->av[pos + 1];
	}
	if (search_in_hist_parser(fc, 1) == FAILURE)
		return (NULL);
	hist = fc->shell->hist;
	if (!(tmp = replace_occurances(tabl[0], tabl[1],
			ft_strdup(fc->hist_first->s))))
		return (NULL);
	ft_strdel(&hist->s);
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
	if ((t = get_tree(hist->s)))
		ft_free_tree(exec_tree(t, fc->shell));
}