/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expantion_tools.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptruffau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/08 16:13:02 by ptruffau          #+#    #+#             */
/*   Updated: 2019/03/19 19:04:57 by stdenis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <shell42.h>

int	get_content_size(char *s)
{
	int i;

	i = 2;
	while (s[i] && s[i] != '}')
	{
		if (s[i] == '$' && s[i + 1] == '{')
			i = i + get_content_size(&s[i]) + 2;
		i++;
	}
	return (i - 2);
}
