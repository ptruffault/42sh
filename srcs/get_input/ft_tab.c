/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tab.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adi-rosa <adi-rosa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/05 14:52:47 by adi-rosa          #+#    #+#             */
/*   Updated: 2019/04/24 17:06:32 by fstadelw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "ft_printf.h"
#include "shell42.h"
#include "get_input.h"

static void	autocompletion_printing(t_edit *e, char **tabl, int max_len)
{
	int		x;
	t_shell	*sh;
	int		nb;

	x = -1;
	sh = ft_get_set_shell(NULL);
	ft_putstr("\n");
	nb = (int)e->width / (max_len + 1);
	while (tabl[++x])
	{
		--nb;
		ft_printf("%*-s", max_len + 1, tabl[x]);
		if (nb == 0)
		{
			ft_putstr("\n");
			nb = (int)e->width / (max_len + 1);
		}
	}
	ft_putstr("\n");
	ft_disp(sh);
}

static int	autocompletion_adding(t_edit *e, char **t)
{
	size_t	x;
	char	*tmp;
	size_t	size;

	x = 0;
	if (!e->hist && !e->hist->s)
		return (FAILURE);
	while (e->curr - x > 0
		&& !(ft_strchr(" /;{$|&", e->hist->s[e->curr - x - 1])))
		++x;
	size = e->curr - x;
	if (!(tmp = ft_strpull(e->hist->s, e->hist->s + size, (int)(x - 1), t[0])))
		return (FAILURE);
	ft_strdel(&e->hist->s);
	e->hist->s = tmp;
	e->curr += ft_strlen(t[0]) - x;
	return (SUCCESS);
}

int			tab_handle(t_edit *e)
{
	char	**tabl;
	int		max_len;
	int		total;
	t_shell	*sh;

	max_len = 0;
	total = 0;
	sh = ft_get_set_shell(NULL);
	if (e->mode == 2)
		return (SUCCESS);
	if (sh->heredoc == 1)
		return (ft_add_char('\t', e));
	if (!(tabl = check_line(&max_len, &total, e)))
		return (FAILURE);
	if (total > 1 && e->hist)
		autocompletion_printing(e, tabl, max_len);
	else if (total == 1 && e->hist)
		autocompletion_adding(e, tabl);
	max_len = 0;
	while (tabl[max_len])
		ft_strdel(&tabl[max_len++]);
	free(tabl);
	return (SUCCESS);
}
