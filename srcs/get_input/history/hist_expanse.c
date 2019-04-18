/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hist_expanse.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adi-rosa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/10 11:46:55 by adi-rosa          #+#    #+#             */
/*   Updated: 2019/04/10 11:46:56 by adi-rosa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_input.h"

static int	get_nb_of_hist(t_edit *e, size_t x)
{
	int		nb;
	size_t	size;
	size_t	i;

	nb = -1;
	size = 0;
	if (e->hist->s[x + 1] == '!')
	{
		nb = -1;
		size = 1;
	}
	else if (ft_isdigit(e->hist->s[x + 1]) || e->hist->s[x + 1] == '-')
	{
		nb = ft_atoi(e->hist->s + x + 1);
		i = e->hist->s[x + 1] == '-' ? x + 2 : x + 1;
		while (e->hist->s[i] && ft_isdigit(e->hist->s[i]))
			++i;
		size = i - x - 1;
	}
	if (seek_n_repl_nb(e, x, nb, size) == FAILURE)
		return (FAILURE);
	return (SUCCESS);
}

static int	get_word_of_hist(t_edit *e, size_t x)
{
	size_t	i;
	char	*word;

	if (e->hist->s[x + 1] < 9 || e->hist->s[x] > 32)
	{
		i = x + 1;
		while (e->hist->s[i] && (e->hist->s[i] < 9 || e->hist->s[i] > 32))
			++i;
		if (!(word = ft_strnew(i - x)))
		{
			ft_strdel(&e->hist->s);
			return (FAILURE);
		}
		word = ft_strncpy(word, e->hist->s + x + 1, i - x - 1);
		if (seek_n_repl_str(e, x, word, i) == FAILURE)
		{
			ft_strdel(&word);
			return (FAILURE);
		}
		ft_strdel(&word);
	}
	return (SUCCESS);
}

static int	parse_hist_exp(t_edit *e, size_t x)
{
	if (!e->hist->s[x + 1])
		return (FAILURE);
	if (e->hist->s[x + 1] == '!'
		|| ft_isdigit(e->hist->s[x + 1]) || e->hist->s[x + 1] == '-')
		get_nb_of_hist(e, x);
	else if (e->hist->s[x + 1] < 9 || e->hist->s[x] > 32)
		get_word_of_hist(e, x);
	return (SUCCESS);
}

int			check_for_hist_exp(t_edit *e)
{
	size_t	x;
	int		block;

	x = 0;
	block = FALSE;
	while (e->hist && e->hist->s && e->hist->s[x])
	{
		if (e->hist->s[x] == '\\')
			++x;
		else if (e->hist->s[x] == '\'')
			block = block == TRUE ? 0 : TRUE;
		else if (block == FALSE && e->hist->s[x] == '!')
		{
			if (parse_hist_exp(e, x) == SUCCESS)
				return (SUCCESS);
		}
		if (e->hist->s[x])
			++x;
	}
	return (FAILURE);
}
