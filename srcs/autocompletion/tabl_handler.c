/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   binary_completion.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stdenis <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/18 15:33:46 by stdenis           #+#    #+#             */
/*   Updated: 2019/03/26 17:18:36 by stdenis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell42.h"

static void	ft_swap_strings(char **str, char **str2)
{
	char *swap;

	swap = *str;
	*str = *str2;
	*str2 = swap;
}

int			check_exec(char *file, char *path)
{
	char		*tmp;
	struct stat	file_stat;

	if (!(tmp = ft_strjoin(path, "/")))
		return (0);
	if (!(tmp = ft_stradd(&tmp, file)))
		return (0);
	if (lstat(tmp, &file_stat) < 0)
	{
		ft_strdel(&tmp);
		return (0);
	}
	if (file_stat.st_mode & S_IEXEC)
	{
		ft_strdel(&tmp);
		return (1);
	}
	ft_strdel(&tmp);
	return (0);
}

void		set_null_tabl(char **tabl, int len_env)
{
	int i;

	i = 0;
	while (i < len_env)
	{
		tabl[i] = NULL;
		i++;
	}
}

void		ft_sort_table(char **tabl, int *max_len)
{
	int		i;
	int		j;
	int		len;

	i = 0;
	*max_len = 0;
	while (tabl[i] != 0)
	{
		j = -1;
		len = (int)ft_strlen(tabl[i]);
		if (len > *max_len)
			*max_len = len;
		while (tabl[++j] != 0)
			if (ft_strcmp((char*)tabl[j], (char*)tabl[i]) > 0)
				ft_swap_strings(&tabl[i], &tabl[j]);
		i++;
	}
}

int			add_to_tabl(char ***tabl, char *value, int j)
{
	char	**retabl;
	size_t	i;

	i = 1;
	if (!value)
		return (1);
	if (!(retabl = (char**)malloc(sizeof(char*) * (unsigned int)(j + 2))))
		return (1);
	set_null_tabl(retabl, j + 1);
	if (!(retabl[0] = ft_strdup(value)))
	{
		free(retabl);
		return (1);
	}
	j = 0;
	while ((*tabl)[j] != NULL)
	{
		retabl[i] = (*tabl)[j++];
		i++;
	}
	free(*tabl);
	*tabl = retabl;
	return (0);
}
