/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adi-rosa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/08 14:15:32 by adi-rosa          #+#    #+#             */
/*   Updated: 2019/03/19 13:49:05 by stdenis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <shell42.h>

char	*heredoc_get_input(char *eoi, t_shell *sh)
{
	char	*ret;
	char	*in;

	ret = NULL;
	ft_putstr("\033[00;34mheredoc>\n\033[00m");
	if ((get_input(&in)))
	{
		while (!ft_strequ(in, eoi) && sh->heredoc == 1)
		{
			in = ft_stradd_char(in, '\n');
			ret = ft_strjoin_fr(ret, in);
			ft_putstr("\033[00;34mheredoc>\n\033[00m");
			if ((get_input(&in)))
			{
				ft_strdel(&in);
				ft_strdel(&ret);
				return (NULL);
			}
		}
		ft_strdel(&in);
	}
	return (ret);
}
