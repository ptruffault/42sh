/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_jump_word.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adi-rosa <adi-rosa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/29 12:06:10 by adi-rosa          #+#    #+#             */
/*   Updated: 2019/04/24 16:17:30 by fstadelw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell42.h"
#include "get_input.h"

void	ft_jp_word_right(t_edit *e)
{
	size_t	x;

	x = e->curr;
	while (e->hist->s[x] && ft_isspace(e->hist->s[x]) == 1)
		x++;
	while (e->hist->s[x] && ft_isspace(e->hist->s[x]) == 0)
		x++;
	e->curr = x;
}

void	ft_jp_word_left(t_edit *e)
{
	size_t	x;

	x = e->curr;
	while (x > 0 && ft_isspace(e->hist->s[x]) == 1)
		x--;
	while (x > 0 && ft_isspace(e->hist->s[x]) == 0)
		x--;
	e->curr = x;
}
