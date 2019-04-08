/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tab.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adi-rosa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/05 14:52:47 by adi-rosa          #+#    #+#             */
/*   Updated: 2019/04/05 14:52:48 by adi-rosa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_input.h"

static void	autocompletion_printing(t_edit *e, char **tabl, int max_len)
{
	int		x;
	t_shell *sh;
	int nb;

	x = -1;
	sh = ft_get_set_shell(NULL);
	ft_putstr("\n");
	nb = e->width / (max_len + 1);
	while (tabl[++x])
	{
		--nb;
		ft_printf("%*-s", max_len + 1, tabl[x]);
		if (nb == 0)
		{
			ft_putstr("\n");
			nb = e->width / (max_len + 1);
		}
	}
	ft_putstr("\n");
	ft_disp(sh);
}

int		autocompletion_adding(t_edit *e, char **tabl)
{
	size_t	x;
	char	*tmp;

	x = 0;
	while (e->curr - x  > 0 && !(ft_strchr(" /;", e->hist->s[e->curr - x - 1])))
		++x;
	if (!(tmp = ft_strpull(e->hist->s, e->hist->s + e->curr - x, x - 1, tabl[0])))
		return (FAILURE);
	ft_strdel(&e->hist->s);
	e->hist->s = tmp;
	e->curr += ft_strlen(tabl[0]) - x;
	return (SUCCESS);
}

int	tab_handle(t_edit *e)
{
	char	**tabl;
	int		max_len;
	int		total;

	max_len = 0;
	total = 0;
	t_shell	*sh;
	sh = ft_get_set_shell(NULL);
	if (sh->heredoc == 1)
	{
		ft_add_char('\t', e);
		return (SUCCESS);
	}
	else
	{
		if (!(tabl = check_line(&max_len, &total, e)))
			return (FAILURE);
		if (total > 1)
			autocompletion_printing(e, tabl, max_len);
		else if (total == 1)
			autocompletion_adding(e, tabl);
		max_len = 0;
		while (tabl[max_len])
			ft_strdel(&tabl[max_len++]);
		free(tabl);
	}
	return (SUCCESS);
}
