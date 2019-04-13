/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_new_path.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptruffau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/08 16:36:20 by ptruffau          #+#    #+#             */
/*   Updated: 2018/06/08 16:37:16 by ptruffau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

char	*ft_get_prev_path(char *path)
{
	char	*ret;
	int		len;
	int		i;

	ret = NULL;
	if (ft_strchr(path, '/'))
	{
		len = ft_strlen(path);
		i = len - 1;
		while (i > 0 && path[i] != '/')
			i--;
		path[i] = '\0';
		ret = path;
	}
	return (ret);
}

char	*ft_new_path(char *s1, char *s2)
{
	char	*new_path;
	size_t	path_len;
	size_t	len;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	new_path = NULL;
	path_len = ft_strlen(s1);
	len = path_len + ft_strlen(s2) + 1;
	if (!(new_path = ft_strnew(len)))
		return (NULL);
	while (i < len)
	{
		if (i < path_len)
			new_path[i] = s1[i];
		else if (i == path_len)
			new_path[i] = '/';
		else
			new_path[i] = s2[j++];
		i++;
	}
	new_path[i] = '\0';
	return (new_path);
}
