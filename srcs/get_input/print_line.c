/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptruffau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/13 13:09:39 by ptruffau          #+#    #+#             */
/*   Updated: 2019/02/09 11:21:49 by adi-rosa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <get_input.h>
#include <curses.h>

void		ft_delete_line(t_edit *e)
{
	curs_reset(e);
	term_actions("cd");
}

static void	print_background(t_edit *e, int pos, int size)
{
	ft_putstr(JAUNE);
	ft_putstr(tparm(tgetstr("AB", NULL), COLOR_WHITE));
	write(1, e->hist->s + pos, size);
	ft_putstr(NORMAL);
	term_actions("me");
}

void ft_print_edited(t_edit *e)
{
	ft_delete_line(e);
	e->curr = ft_strlen(e->hist->s);
	ft_putstr(tparm(tgetstr("AF", NULL), COLOR_YELLOW));
	write(1, e->hist->s, ft_strlen(e->hist->s));
	ft_putstr(NORMAL);
	term_actions("ve");
	ft_putchar('\n');
}

void ft_print_fast(t_edit *e)
{
	uintmax_t pos;
	uintmax_t size;
	int i;

	ft_delete_line(e);
	pos = 0;
	size = 1;
	term_actions((size_t)e->curr == ft_strlen(e->hist->s) ? "ve" : "vi");
	i = ft_strlen(e->hist->s);
	if (e->select == -1 || e->select == e->curr)
		pos = e->curr;
	else
	{
		pos = e->select > e->curr ? e->curr : e->select;
		size += e->select > e->curr ? e->select - e->curr : e->curr - e->select;
	}
	write(1, e->hist->s, pos);
	print_background(e, pos, size);
	if (e->curr != i && e->select != i)
		write(1, e->hist->s + pos + size, i - pos - size);
	e->pos = i;
}

void		ft_print_line(t_edit *e)
{
	e->print_modes[e->mode](e);
}
