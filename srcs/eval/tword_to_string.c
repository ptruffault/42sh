/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tword_to_string.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptruffau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/28 19:53:01 by ptruffau          #+#    #+#             */
/*   Updated: 2019/04/28 19:53:02 by ptruffau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell42.h"

char		*tword_to_string(t_word *w)
{
	char *str;

	str = NULL;
	while (w)
	{
		if (!(str = ft_strappend(&str, w->word))
			|| (w->next && !(str =  ft_stradd_char(str, ' '))))
			return (NULL);
		w = w->next;
	}
	return (str);
}
