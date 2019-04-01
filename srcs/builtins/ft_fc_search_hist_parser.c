/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fc_search_hist_parser.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adi-rosa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/01 14:30:52 by adi-rosa          #+#    #+#             */
/*   Updated: 2019/04/01 14:30:53 by adi-rosa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell42.h"

static t_hist  *search_by_number(t_hist *first, int nb)
{
    if (nb < 0)
        return (search_by_number_from_first(first, nb));
    else
        return (search_by_number_from_last(first, nb));
}

int             search_in_hist_parser(t_fc *fc)
{
    t_hist  *hist;

    hist = fc->shell->hist;
    if (fc->first != 0)
    {
        if (!(fc->hist_first = search_by_number(fc->hist, fc->first)))
            return (FAILURE);
    }
    else if (fc->first_)
    {
        if (!(fc->hist_first = search_by_occurence(fc->hist, fc->first_)))
            return (FAILURE);
    }
    if (fc->last != 0)
    {
        if (!(fc->hist_last = search_by_number(fc->hist, fc->last)))
            return (FAILURE);
    }
    else if (fc->last_)
    {
        if (!(fc->hist_last = search_by_occurence(fc->hist, fc->last_)))
            return (FAILURE);
    }
    return (SUCCESS);
}
