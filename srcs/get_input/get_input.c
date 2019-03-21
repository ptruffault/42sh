/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_input.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptruffau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/13 13:12:58 by ptruffau          #+#    #+#             */
/*   Updated: 2019/03/21 12:50:52 by stdenis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <get_input.h>

int		ft_update_hist(t_shell *sh)
{
	char	*hi_path;
	t_hist *hist;

	if (sh->e.hist && sh->e.hist->s && sh->e.hist->s[0] != '\0')
	{
		if ((hi_path = get_tenvv_val(sh->env, "HISTORY")))
			ft_write_in_file(hi_path, sh->e.hist->s);
		if (!sh->e.hist->prev)
			sh->hist = sh->e.hist;
		else
		{
			hist = sh->e.hist;
			while (hist->prev)
				hist = hist->prev;
			ft_strdel(&hist->s);
			if (!(hist->s = ft_strdup(sh->e.hist->s)))
			{
				free(hist);
				return (FAILURE);
			}
			sh->e.hist = hist;
			sh->hist = sh->e.hist;
		}
		ft_print_edited(&sh->e);
	}
	else
	{
		while (sh->e.hist->prev)
			sh->e.hist = sh->e.hist->prev;
		ft_strdel(&sh->e.hist->s);
		sh->e.hist = sh->e.hist->next;
		free(sh->e.hist->prev);
		sh->e.hist->prev = NULL;
	}
	ft_set_old_term(sh);
	return (SUCCESS);
}

int			get_input(char	**line)
{
	t_shell			*sh;
	unsigned long	buf;

	sh = ft_get_set_shell(NULL);
	if (!isatty(0) || sh->interactive == FALSE || !init_tedit(sh)
		|| !ft_setup_edit_term(sh))
		return (FAILURE);
	buf = 0;
	while (sh->e.edited == FALSE && read(0, &buf, 8) > 0)
	{
		buf = handle_input(buf, &sh->e);
		if (buf == 9)
		{
			ft_set_old_term(sh);
			return (4);
		}
		else if (buf == 10 && (!sh->e.hist || !sh->e.hist->s || !*sh->e.hist->s))
		{
			ft_set_old_term(sh);
			return (0);
		}
		if (sh->hist)
			ft_print_line(&sh->e);
		buf = 0;
	}
	*line = ft_strdup(sh->e.hist->s);
	return (ft_update_hist(sh));
}
