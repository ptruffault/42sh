/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptruffau <ptruffau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/13 13:21:10 by ptruffau          #+#    #+#             */
/*   Updated: 2019/04/24 16:18:41 by fstadelw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell42.h"
#include "get_input.h"

static int	delete_simple_left(t_edit *e)
{
	size_t	i;
	size_t	j;
	char	*tmp;

	if (e->curr < 1)
		return (SUCCESS);
	i = 0;
	j = 0;
	if (!(tmp = ft_strnew(ft_strlen(e->hist->s) - 1)) || !e->hist
		|| !e->hist->s)
		return (FAILURE);
	ft_delete_line(e);
	while (e->hist->s[j])
	{
		if (j != e->curr - 1)
			tmp[i++] = e->hist->s[j];
		j++;
	}
	tmp[i] = '\0';
	ft_strdel(&e->hist->s);
	e->hist->s = tmp;
	curr_move_left(e);
	ft_print_fast(e);
	return (SUCCESS);
}

static int	delete_multiple_left(t_edit *e, size_t stop)
{
	char	*tmp;
	size_t	i;
	size_t	x;
	size_t	size;

	i = (e->curr > e->select_pos ? e->curr : e->select_pos);
	if (!(tmp = ft_strnew(ft_strlen(e->hist->s) - (i - stop)))
		|| !e->hist || !e->hist->s)
		return (FAILURE);
	ft_delete_line(e);
	ft_strncpy(tmp, e->hist->s, stop);
	x = stop;
	while (e->hist->s[i++])
		tmp[x++] = e->hist->s[i];
	tmp[x] = '\0';
	ft_strdel(&e->hist->s);
	e->hist->s = tmp;
	e->select_pos = 0;
	e->select = -1;
	e->curr = e->curr > e->select_pos ? e->select_pos : e->curr;
	if (e->curr > (size = ft_strlen(e->hist->s)))
		e->curr = size;
	curr_go_last(e);
	ft_print_fast(e);
	return (SUCCESS);
}

int			ft_add_char(char buf, t_edit *e)
{
	char	*tmp;

	if (e->select != -1)
		delete_left(e);
	if (!e->hist || ((!ft_isprint(buf) || !e->hist->s) && buf != 9))
		return (SUCCESS);
	if (e->max_char < e->pos + 1)
	{
		if (e->curr + 1 > e->max_char)
			e->pos_z += 1;
		if (e->curr + 1 < e->max_char)
			e->pos_y += 1;
	}
	ft_delete_line(e);
	tmp = e->hist->s;
	e->hist->s = ft_strsub(tmp, 0, (size_t)e->curr);
	e->hist->s = ft_strinsert_char(&e->hist->s, buf, tmp + e->curr);
	ft_strdel(&tmp);
	e->curr++;
	if (e->select != -1)
		e->select = -1;
	ft_print_fast(e);
	return (SUCCESS);
}

void		delete_left(t_edit *e)
{
	size_t	stop;

	if (e->select == -1)
		delete_simple_left(e);
	else
	{
		stop = e->curr > e->select_pos ? e->select_pos : e->curr;
		delete_multiple_left(e, stop);
	}
	e->select = -1;
}

void		delete_on(t_edit *e)
{
	size_t	i;
	size_t	j;
	size_t	size;
	char	*tmp;

	e->select = -1;
	if (e->curr == (size = ft_strlen(e->hist->s)))
		return ;
	i = 0;
	j = 0;
	if (!(tmp = ft_strnew(size - 1)))
		return ;
	ft_delete_line(e);
	while (e->hist->s[j])
	{
		if (j != e->curr)
			tmp[i++] = e->hist->s[j];
		j++;
	}
	tmp[i] = '\0';
	ft_strdel(&e->hist->s);
	e->hist->s = tmp;
	ft_print_fast(e);
	return ;
}
