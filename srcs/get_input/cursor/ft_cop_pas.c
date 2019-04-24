/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cop_pas.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adi-rosa <adi-rosa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/23 13:01:07 by adi-rosa          #+#    #+#             */
/*   Updated: 2019/04/24 16:17:22 by fstadelw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell42.h"
#include "get_input.h"

void	ft_copy(t_edit *e)
{
	t_shell	*sh;
	size_t	pos;
	size_t	size;

	sh = ft_get_set_shell(NULL);
	if (e->curr == e->select_pos || e->select == -1)
		return ;
	pos = 0;
	size = 0;
	if (e->curr > e->select_pos)
	{
		pos = e->select_pos;
		size = e->curr - e->select_pos;
	}
	else if (e->curr < e->select_pos)
	{
		pos = e->curr;
		size = e->select_pos - e->curr;
	}
	ft_strdel(&sh->clipboard);
	if ((sh->clipboard = ft_strnew(size)))
		sh->clipboard = ft_strncpy(sh->clipboard, e->hist->s + pos, size);
}

void	ft_paste(t_edit *e)
{
	t_shell	*sh;
	size_t	x;
	size_t	b;
	size_t	c;
	char	*tmp;

	sh = ft_get_set_shell(NULL);
	if (sh->clipboard && e->select != -1)
		delete_left(e);
	if (sh->clipboard
		&& (tmp = ft_strnew(ft_strlen(e->hist->s) + ft_strlen(sh->clipboard))))
	{
		b = 0;
		x = 0;
		c = 0;
		while (x < e->curr)
			tmp[b++] = e->hist->s[x++];
		while (sh->clipboard[c])
			tmp[b++] = sh->clipboard[c++];
		e->curr = b;
		while (e->hist->s[x])
			tmp[b++] = e->hist->s[x++];
		ft_strdel(&e->hist->s);
		e->hist->s = tmp;
	}
}
