/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adi-rosa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/01 17:57:42 by adi-rosa          #+#    #+#             */
/*   Updated: 2019/03/19 11:43:05 by stdenis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <get_input.h>

void	update_input(t_edit *e, char *s)
{
	if (s == NULL)
		ft_delete_line(e);
	ft_strdel(&e->hist->s);
	if (s != NULL)
		e->hist->s = s;
	else if (s == NULL)
		e->hist->s = ft_strnew(3);
	e->curr = ft_strlen(s);
}

static void bottom_start_hist(t_edit *e, char *input)
{
	t_hist *hist;

	hist = e->hist->next;
	while (hist)
	{
		if (ft_str_startwith(hist->s, input) != 0)
			{
				e->hist = hist;
				return ;
			}
		hist = hist->next;
	}
}

void	hist_move_up(t_edit *e)
{
	ft_delete_line(e);
	if (!e->hist->next)
		return ;
	if (!e->hist->prev && e->hist->s[0] != '\0' && e->hist->next)
		{
			bottom_start_hist(e, e->hist->s);
		}
	else
		e->hist = e->hist->next;
	e->curr = ft_strlen(e->hist->s);
	e->select = -1;
	ft_print_line(e);
}

void	hist_move_do(t_edit *e)
{
	ft_delete_line(e);
	if (!e->hist->prev)
		return ;
	e->hist = e->hist->prev;
	e->curr = ft_strlen(e->hist->s);
	e->select = -1;
	ft_print_line(e);
}
