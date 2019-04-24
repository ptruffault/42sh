/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   use_termcaps.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adi-rosa <adi-rosa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/05 12:31:56 by adi-rosa          #+#    #+#             */
/*   Updated: 2019/04/24 17:06:04 by fstadelw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "shell42.h"
#include "get_input.h"

static int	execute_tputs(int c)
{
	write(0, &c, 1);
	return (0);
}

static int	do_tputs(const char *str, int affcnt, int (*putc)(int))
{
	if (str != NULL)
		return (tputs(str, affcnt, putc));
	return (-1);
}

char		*get_tgetstr(const char *id, char **area)
{
	char	*rtn;
	char	*tmp;

	tmp = ft_strdup(id);
	if (tmp == NULL)
		return (NULL);
	rtn = tgetstr(tmp, area);
	ft_strdel(&tmp);
	return (rtn);
}

int			term_actions(const char *id)
{
	char	*str;

	str = get_tgetstr(id, NULL);
	if (str)
		do_tputs(str, 1, execute_tputs);
	else
		return (FAILURE);
	return (SUCCESS);
}

int			term_goto(char *cmd, int row, int col)
{
	char	*str;
	char	*go;

	go = NULL;
	str = get_tgetstr(cmd, NULL);
	if (str)
		go = tgoto(str, row, col);
	if (go)
		do_tputs(go, 1, execute_tputs);
	return (SUCCESS);
}
