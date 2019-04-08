/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_utility.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stdenis <stdenis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/15 13:38:24 by stdenis           #+#    #+#             */
/*   Updated: 2019/03/17 18:34:45 by stdenis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell42.h"

t_hash			**init_htable(void)
{
	t_hash		**table;
	int			i;

	i = -1;
	if (!(table = (t_hash**)malloc(sizeof(t_hash*) * (HASHTABLE_SIZE))))
		return (NULL);
	while (++i < HASHTABLE_SIZE)
		table[i] = NULL;
	return (table);
}

unsigned int	ft_hash(const char *str)
{
	unsigned int	hashval;
	unsigned int	c;

	hashval = 0;
	while ((c = *((unsigned char *)str++)))
		hashval += (hashval << 5) + c;
	return (hashval % HASHTABLE_SIZE);
}
