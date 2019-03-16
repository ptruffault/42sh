/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptruffau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/13 13:21:10 by ptruffau          #+#    #+#             */
/*   Updated: 2019/02/18 15:42:21 by adi-rosa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <get_input.h>

void		ft_add_char(char buf, t_edit *e)
{
	int i;
	int size;

	if (e->select != -1)
	{
		delete_left(e);
		e->select = -1;
	}
	if (!ft_isprint(buf) || !e->hist->s)
		return ;
	i = ft_strlen(e->hist->s);
	size = ft_strlen(e->hist->s) + 1;
	while (i > 1 && i > e->curr)
	{
		e->hist->s[i] = e->hist->s[i - 1];
		i--;
	}
	e->hist->s[e->curr] = buf;
	e->hist->s = ft_realloc(e->hist->s, size, size + 1);
	e->hist->s[size] = '\0';
	e->curr++;
	if (e->select != -1)
		e->select = -1;
}

static void	delete_simple_left(t_edit *e)
{
	int		i;
	int		j;
	char	*tmp;

	if (e->curr < 1)
		return ;
	i = 0;
	j = 0;
	tmp = ft_strnew(ft_strlen(e->hist->s));
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
}

static void	delete_multiple_left(t_edit *e, int stop)
{
	char	*tmp;
	int		i;
	int		x;

	x = 0;
	i = 0;
	tmp = ft_strnew(ft_strlen(e->hist->s));
	while (e->hist->s[i] && i < stop)
		tmp[x++] = e->hist->s[i++];
	i = (e->curr > e->select ? e->curr : e->select);
	if (e->hist->s[i])
		++i;
	while (e->hist->s[i])
		tmp[x++] = e->hist->s[i++];
	tmp[x] = '\0';
	ft_strdel(&e->hist->s);
	e->hist->s = tmp;
	e->curr = e->curr > e->select ? e->select : e->curr;
	if (e->curr > (int)ft_strlen(e->hist->s))
		e->curr = ft_strlen(e->hist->s);
}

void		delete_left(t_edit *e)
{
	int		stop;

	if (e->select == -1)
		delete_simple_left(e);
	else
	{
		stop = e->curr > e->select ? e->select : e->curr;
		delete_multiple_left(e, stop);
	}
	e->select = -1;
}

void		delete_on(t_edit *e)
{
	int		i;
	int		j;
	char	*tmp;

	e->select = -1;
	if ((size_t)e->curr == (size_t)ft_strlen(e->hist->s))
		return ;
	i = 0;
	j = 0;
	tmp = ft_strnew(ft_strlen(e->hist->s));
	while (e->hist->s[j])
	{
		if (j != e->curr)
			tmp[i++] = e->hist->s[j];
		j++;
	}
	tmp[i] = '\0';
	ft_strdel(&e->hist->s);
	e->hist->s = tmp;
}
