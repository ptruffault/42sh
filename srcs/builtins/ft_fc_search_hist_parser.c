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

t_hist *search_in_hist(t_fc *fc)
{
    t_hist  *hist;

    hist = fc->shell->hist;
    if (fc->first != 0)
    {
        if (!(fc->hist_first = search_by_number(fc->first)))
            return (NULL);
    }
    else if (fc->first_)
    {
        if (!(fc->hist_first = search_by_occurence(fc->first_)))
            return (NULL);
    }
    if (fc->last != 0)
    {
        if (!(fc->hist_last = search_by_number(fc->last)))
            return (NULL);
    }
    else if (fc->last_)
    {
        if (!(fc->hist_last = search_by_occurence(fc->last_)))
            return (NULL);
    }
    return (NULL);
}
