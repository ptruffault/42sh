/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fc_search_hist.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adi-rosa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/01 15:07:02 by adi-rosa          #+#    #+#             */
/*   Updated: 2019/04/01 15:07:02 by adi-rosa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell42.h"

t_hist	*search_by_number_from_first(t_hist *first, int nb)
{
	t_hist	*hist;

	hist = first;
	while (hist && hist->next && nb < -1)
	{
		hist = hist->next;
		++nb;
	}
	return (hist);
}

t_hist	*search_by_number_from_last(t_hist *first, int nb)
{
	t_hist	*hist;

	hist = first;
	if (hist && hist->nb < nb)
		return (hist);
	while (hist && hist->next && hist->nb != nb)
		hist = hist->next;
	if (hist && hist->nb != nb)
	{
		error("fc: history specification is out of range", "Number too little");
		return (NULL);
	}
	return (hist);
}

t_hist	*search_by_occurence(t_hist *first, char *to_search)
{
	t_hist	*hist;

	hist = first;
	while (hist && hist->next && ft_str_startwith(hist->s, to_search) == 0)
		hist = hist->next;
	if (hist && ft_str_startwith(hist->s, to_search) == 1)
		return (hist);
	error("fc: history specification is out of range", to_search);
	return (NULL);
}
