/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strappend.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stdenis <stdenis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/10 10:52:45 by stdenis           #+#    #+#             */
/*   Updated: 2019/01/28 20:32:02 by stdenis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strappend_fr(char **str, char **end)
{
	char	*rtn;

	rtn = ft_strjoin(*str, *end);
	ft_strdel(str);
	ft_strdel(end);
	*str = rtn;
	return (rtn);
}

char	*ft_strappend(char **str, const char *end)
{
	char	*rtn;

	rtn = ft_strjoin(*str, end);
	ft_strdel(str);
	*str = rtn;
	return (rtn);
}
