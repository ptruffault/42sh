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

static void	autocompletion_printing(t_edit *e, char **tabl, int max_len, int total)
{
	int		x;
	t_shell *sh;
	int nb;

	x = -1;
	(void)e;
	(void)total;
	sh = ft_get_set_shell(NULL);
	ft_putstr("\n");
	nb = e->width / max_len;
	while (tabl[++x])
	{
		ft_printf("%*s", max_len, tabl[x]);
		if (nb == 0)
		{
			ft_putstr("\n");
			nb = e->width / max_len;
		}
		--nb;
	}
	ft_disp(sh);
}

int	tab_handle(t_edit *e)
{
	char	**tabl;
	int		max_len;
	int		total;
	char	*tmp;

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
			autocompletion_printing(e, tabl, max_len, total);
		else if (total == 1)
		{
			while (e->hist->s[e->curr] != ' ' && e->curr > 0)
				e->curr--;
			if (e->hist->s[e->curr])
				e->hist->s[++e->curr] = '\0';
			if (!(tmp = ft_stradd(&e->hist->s, tabl[0])))
				return (FAILURE);
			e->curr += ft_strlen(tabl[0]);
			e->hist->s = tmp;
		}
	}
	return (SUCCESS);
}
