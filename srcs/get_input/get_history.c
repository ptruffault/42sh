/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adi-rosa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/01 17:47:37 by adi-rosa          #+#    #+#             */
/*   Updated: 2019/02/01 17:51:58 by adi-rosa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <shell42.h>

int		ft_isparenth(char c)
{
	if (c == '{' || c == '(')
		return (1);
	else if (c == '}' || c == ')')
		return (2);
	return (0);
}

t_hist	*new_hist(void)
{
	t_hist	*n;

	if (!(n = (t_hist *)malloc(sizeof(t_hist))))
		return (NULL);
	n->s = NULL;
	n->next = NULL;
	n->prev = NULL;
	return (n);
}

t_hist	*add_hist(t_hist *head, char *s)
{
	t_hist	*new;

	if (!(new = new_hist()))
		return (NULL);
	new->s = ft_strdup(s);
	new->next = head;
	return (new);
}

t_hist	*ft_read_hist(int i, char **arr)
{
	t_hist *new;
	t_hist *tmp;

	if (!(new = new_hist()))
		return (NULL);
	tmp = new;
	while (i >= 0)
	{
		if ((tmp->s = ft_strdup(arr[i--])))
		{
			if (!(tmp->next = new_hist()))
				return (ft_free_thist(new));
			tmp->next->prev = tmp;
			tmp = tmp->next;
		}
	}
	tmp = tmp->prev;
	free(tmp->next);
	tmp->next = NULL;
	return (new);
}

t_hist	*init_hist(char *hist)
{
	t_hist	*new;
	int		fd;
	char	**arr;
	int		i;

	new = NULL;
	if ((fd = open(hist, O_RDWR | O_CREAT | O_NOFOLLOW, S_IRWXU | S_IRWXG | S_IRWXO)) >= 0)
	{
		if ((arr = ft_get_txt(fd)))
		{
			if ((i = ft_strarrlen(arr) - 1) > 0)
				new = ft_read_hist(i, arr);
			arr = ft_freestrarr(arr);
		}
		ft_close(fd);
	}
	else
		perror(hist);
	return (new);
}
