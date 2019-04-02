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

int		check_exec(char *file, char *path)
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

int		add_to_tabl(char ***tabl, char *value, int j)
{
	char	**retabl;
	size_t	i;

	i = 1;
	if (!(retabl = (char**)malloc(sizeof(char*) * (j + 2))))
		return (1);
	retabl[0] = ft_strdup(value);
	j = 0;
	while ((*tabl)[j] != NULL)
	{
		retabl[i] = (*tabl)[j++];
		i++;
	}
	retabl[i] = NULL;
	free(*tabl);
	*tabl = retabl;
	return (0);
}
