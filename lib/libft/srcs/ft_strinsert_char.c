/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strinsert_char.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stdenis <stdenis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/10 10:52:45 by stdenis           #+#    #+#             */
/*   Updated: 2019/01/28 20:32:02 by stdenis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strinsert_char(char **str, char c, char *end)
{
	char	*rtn;
	char	buff[2];

	buff[0] = c;
	buff[1] = '\0';
	rtn = ft_strjoin(*str, buff);
	if (end[0] != '\0' && rtn)
		rtn = ft_strappend(&rtn, end);
	if (rtn)
	{
		ft_strdel(str);
		*str = rtn;
		return (rtn);
	}
	return (*str);
}
