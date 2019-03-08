/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adi-rosa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/01 17:57:42 by adi-rosa          #+#    #+#             */
/*   Updated: 2019/02/01 17:59:51 by adi-rosa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/get_input.h"

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

/*static char *bottom_start_hist(t_hist *hist, char *input)
{
	int x;

	while (hist)
	{
		if ((x = ft_strstr(hist->s, input) != 0))
			break ;
		hist = hist->next;
	}
	if (x != 0)
	{
		ft_strdel(&input);
		input = ft_strdup(hist->s);
	}
	return (input);
}*/

void	hist_move_up(t_edit *e)
{
	//t_hist *hist;

	ft_delete_line(e);
	if (!e->hist->next)
		return ;
	//if (!e->hist->prev && e->hist->s[0] != '0' && e->hist->next)
	//	{
	//		hist = e->hist->next;
	//		e->hist->s = bottom_start_hist(hist, e->hist->s);
	//	}
	//else
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
