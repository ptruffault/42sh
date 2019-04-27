/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptruffau <ptruffau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/16 13:28:58 by ptruffau          #+#    #+#             */
/*   Updated: 2019/04/24 16:44:36 by fstadelw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

static size_t	count_word(char const *s, char c)
{
	size_t		i;
	size_t		rtn;

	i = 1;
	rtn = 0;
	if (s[0] == '\0')
		return (0);
	if (s[0] != c)
		rtn++;
	while (s[i] != '\0')
	{
		if (s[i - 1] == c && s[i] != c)
			rtn++;
		i++;
	}
	return (rtn);
}

static char		*get_word(char const *s, size_t *pos, char c)
{
	char		*rtn;
	size_t		beg;
	size_t		end;

	beg = *pos;
	while (s[beg] == c)
		beg++;
	end = beg;
	while (s[end] != c && s[end] != '\0')
		end++;
	if (beg == end)
		return (NULL);
	rtn = ft_strnew(end - beg);
	if (rtn != (char *)NULL)
	{
		ft_strncpy(rtn, &s[beg], end - beg);
		*pos = end;
	}
	return (rtn);
}

char			**ft_strsplit(char const *s, char c)
{
	char		**rtn;
	size_t		nb_word;
	size_t		cur_word;
	size_t		j;

	if (s == (char *)NULL)
		return ((char **)NULL);
	nb_word = count_word(s, c);
	rtn = (char **)malloc(sizeof(char *) * (nb_word + 1));
	if (rtn == (char **)NULL)
		return ((char **)NULL);
	rtn[nb_word] = (char *)NULL;
	cur_word = 0;
	j = 0;
	while (cur_word < nb_word)
	{
		rtn[cur_word] = get_word(s, &j, c);
		cur_word++;
	}
	return (rtn);
}
