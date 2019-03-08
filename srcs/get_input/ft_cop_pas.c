/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cop_pas.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adi-rosa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/23 13:01:07 by adi-rosa          #+#    #+#             */
/*   Updated: 2019/03/08 13:31:23 by adi-rosa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/get_input.h"

void	ft_copy(t_edit *e)
{
	t_shell	*sh;
	int		pos;
	int		size;

	sh = ft_get_set_shell(NULL);
	if (e->curr == e->select || e->select == -1)
		return ;
	pos = 0;
	size = 0;
	if (e->curr > e->select)
	{
		pos = e->select;
		size = e->curr - e->select;
	}
	else if (e->curr < e->select)
	{
		pos = e->curr;
		size = e->select - e->curr;
	}
	if (sh->clipboard)
		ft_strdel(&sh->clipboard);
	if ((sh->clipboard = ft_strnew(size + 1)))
		sh->clipboard = ft_strncpy(sh->clipboard, e->hist->s + pos, size + 1);
}

void	ft_paste(t_edit *e)
{
	t_shell *sh;
	int		x;
	int		b;
	int		c;
	char	*tmp;

	sh = ft_get_set_shell(NULL);
	if (sh->clipboard
	&& (tmp = ft_strnew(ft_strlen(e->hist->s) + ft_strlen(sh->clipboard) + 1)))
	{
		b = 0;
		x = 0;
		c = 0;
		while (x < e->curr)
			tmp[b++] = e->hist->s[x++];
		while (sh->clipboard[c])
			tmp[b++] = sh->clipboard[c++];
		while (e->hist->s[x])
			tmp[b++] = e->hist->s[x++];
		ft_strdel(&e->hist->s);
		e->hist->s = tmp;
	}
	e->select = -1;
}
