/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   seek_n_replace.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adi-rosa <adi-rosa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/10 14:54:40 by adi-rosa          #+#    #+#             */
/*   Updated: 2019/04/24 16:20:25 by fstadelw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell42.h"
#include "get_input.h"

int		seek_n_repl_str(t_edit *e, size_t x, char *word, size_t i)
{
	t_hist	*hist;
	char	*tmp;
	int		b;

	if (!(hist = ft_get_set_shell(NULL)->hist))
		return (FAILURE);
	while (hist->prev)
		hist = hist->prev;
	if (!hist->next)
	{
		error("No history", NULL);
		return (FAILURE);
	}
	hist = hist->next;
	if (!(hist = search_by_occurence(hist, word)))
		return (FAILURE);
	ft_delete_line(e);
	b = (int)i - x - 1;
	if (!(tmp = ft_strpull(e->hist->s, e->hist->s + x, b, hist->s)))
		return (FAILURE);
	ft_strdel(&e->hist->s);
	e->hist->s = tmp;
	curr_go_last(e);
	ft_print_fast(e);
	return (SUCCESS);
}

int		seek_n_repl_nb(t_edit *e, size_t x, int nb, size_t size)
{
	t_hist	*hist;
	char	*tmp;

	if (!(hist = ft_get_set_shell(NULL)->hist))
		return (FAILURE);
	while (hist->prev)
		hist = hist->prev;
	if (!hist->next)
		return (error("No history", NULL) == FAILURE ? FAILURE : FAILURE);
	hist = hist->next;
	if (nb < 0)
		hist = search_by_number_from_first(hist, nb);
	else
		hist = search_by_number_from_last(hist, nb);
	if (!hist)
		return (FAILURE);
	ft_delete_line(e);
	if (!(tmp = ft_strpull(e->hist->s, e->hist->s + x, (int)size, hist->s)))
		return (FAILURE);
	ft_strdel(&e->hist->s);
	e->hist->s = tmp;
	curr_go_last(e);
	ft_print_fast(e);
	return (SUCCESS);
}
