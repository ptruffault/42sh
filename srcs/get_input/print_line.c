/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptruffau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/13 13:09:39 by ptruffau          #+#    #+#             */
/*   Updated: 2019/03/26 17:21:55 by stdenis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <get_input.h>

static void	print_background(t_edit *e, size_t pos, size_t size)
{
	ft_putstr(JAUNE);
	term_actions("mr");
	if (e->hist->s[pos] == '\n')
		ft_putstr("\x1B[7m ");
	write(0, e->hist->s + pos, size);
	ft_putstr(NORMAL);
	term_actions("me");
}

void		ft_delete_line(t_edit *e)
{
	curs_reset(e);
	term_actions("cd");
}

void		ft_print_edited(t_edit *e)
{
	ft_delete_line(e);
	e->curr = ft_strlen(e->hist->s);
	ft_putstr("\x1B[33m");
	write(1, e->hist->s, e->curr);
	ft_putstr(NORMAL);
	term_actions("ve");
	ft_putchar('\n');
}

void		ft_print_fast(t_edit *e)
{
	size_t pos;
	size_t size;
	size_t i;

	size = 1;
	i = ft_strlen(e->hist->s);
	term_actions((e->curr == i) ? "ve" : "vi");
	if (e->select == -1 || e->select_pos == e->curr)
		pos = e->curr;
	else
	{
		pos = (e->select_pos > e->curr) ? e->curr : e->select_pos;
		if (e->select_pos > e->curr)
			size += e->select_pos - e->curr;
		else
			size += e->curr - e->select_pos;
	}
	write(0, e->hist->s + (e->pos_z), (pos - ((size_t)e->pos_z)));
	print_background(e, pos, size);
	if (e->curr != i && e->select_pos != i)
		write(0, e->hist->s + pos + size, i - pos - size - (size_t)e->pos_y);
	e->pos = i;
}

void		ft_print_line(t_edit *e)
{
	ft_delete_line(e);
	if (e && e->hist && e->hist->s)
		e->print_modes[e->mode](e);
}
