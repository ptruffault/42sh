/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_incr_search.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adi-rosa <adi-rosa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/11 13:50:12 by adi-rosa          #+#    #+#             */
/*   Updated: 2019/04/24 16:32:03 by fstadelw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "shell42.h"
#include "get_input.h"

static t_hist	*incr_search_by_occurence(t_hist *first, char *to_search)
{
	t_hist	*hist;

	hist = first;
	while (hist && hist->next && ft_str_startwith(hist->s, to_search) == 0)
		hist = hist->next;
	if (hist && ft_str_startwith(hist->s, to_search) == 1)
		return (hist);
	return (NULL);
}

static size_t	how_much_cr2(char *s)
{
	size_t	i;
	size_t	count;

	i = 0;
	count = 0;
	while (s[i])
	{
		if (s[i] == '\n')
			count++;
		i++;
	}
	return (count);
}

static void		ft_print_search(t_edit *e, t_hist *hist)
{
	size_t		val;
	size_t		cr;

	val = ft_strlen(e->hist->s);
	while (val > e->width)
		val -= e->width;
	if (e->width > val)
		val = e->width - val;
	else
		val = 0;
	if (hist && hist->nb != e->hist->nb)
	{
		e->incr_search = hist->s;
		cr = ft_strlen(hist->s) + (how_much_cr2(hist->s) * e->width);
		e->pos += val + 17 + cr;
		ft_printf("\n(Incr' search): %s", hist->s);
	}
	else
	{
		e->pos += val + 38;
		e->incr_search = NULL;
		ft_printf("\n(Incremental search: no result found)");
	}
}

int				ft_incr_add(t_edit *e)
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

void			ft_incremental_search(t_edit *e)
{
	t_hist *hist;

	if (!(hist = e->hist))
		return ;
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
	ft_print_search(e, hist);
}
