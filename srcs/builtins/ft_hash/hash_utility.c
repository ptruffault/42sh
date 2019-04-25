/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_utility.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stdenis <stdenis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/15 13:38:24 by stdenis           #+#    #+#             */
/*   Updated: 2019/04/24 17:01:46 by fstadelw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "shell42.h"

static int		error_options_hash(int ret, const char *opts)
{
	error("hash: invalid option :", opts);
	ft_putendl_fd("usage: hash [-r] [name ...]", 2);
	return (ret);
}

char			**check_options_hash(char **cmd, t_shell *sh, int *ret)
{
	int			i;

	while (*cmd && (*cmd)[0] == '-')
	{
		i = 0;
		if ((*cmd)[1] == '-')
		{
			cmd++;
			break ;
		}
		while ((*cmd)[++i] != '\0')
		{
			if (!(ft_strchr("-r", (*cmd)[i])))
			{
				*ret = error_options_hash(2, *cmd);
				return (cmd);
			}
			else
				cleaning_htable(sh);
		}
		cmd++;
	}
	return (cmd);
}

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
	while ((c = (unsigned int)*(str++)))
		hashval += (hashval << 5) + c;
	return (hashval % HASHTABLE_SIZE);
}
