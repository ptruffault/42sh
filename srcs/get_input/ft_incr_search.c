/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_incr_search.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adi-rosa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/11 13:50:12 by adi-rosa          #+#    #+#             */
/*   Updated: 2019/04/11 13:50:12 by adi-rosa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <get_input.h>

t_hist	*incr_search_by_occurence(t_hist *first, char *to_search)
{
	t_hist	*hist;

	hist = first;
	while (hist && hist->next && ft_str_startwith(hist->s, to_search) == 0)
		hist = hist->next;
	if (hist && ft_str_startwith(hist->s, to_search) == 1)
		return (hist);
	return (NULL);
}

int		ft_incr_add(t_edit *e)
{
	char	*tmp;

	ft_delete_line(e);
	e->mode = 0;
	if (!e->incr_search)
		return (SUCCESS);
	if (!(tmp = ft_strdup(e->incr_search)))
	{
		e->incr_search = NULL;
		return (SUCCESS);
	}
	ft_strdel(&e->hist->s);
	e->hist->s = tmp;
	curr_go_last(e);
	ft_print_fast(e);
	return (SUCCESS);
}

void	ft_incremental_search(t_edit *e)
{
	t_hist *hist;

	hist = e->hist;
	while (hist->prev)
		hist = hist->prev;
	ft_print_fast(e);
	term_actions("vi");
	if (!hist->next)
	{
		e->mode = 0;
		return ;
	}
	hist = hist->next;
	hist = incr_search_by_occurence(hist, e->hist->s);
	if (hist && e->hist->nb == hist->nb && e->hist->next)
		hist = incr_search_by_occurence(e->hist, e->hist->s);
	if (hist && hist->nb != e->hist->nb)
	{
		e->incr_search = hist->s;
		ft_printf("\n(Incr' search):%s", hist->s);
		e->pos = (e->width - ft_strlen(e->hist->s)) + 15 + ft_strlen(hist->s);
	}
	else
	{
		ft_printf("\n(Incremental search: no result found)");
		e->pos += 37 + e->width;
	}
}
