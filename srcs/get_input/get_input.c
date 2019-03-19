/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_input.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptruffau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/13 13:12:58 by ptruffau          #+#    #+#             */
/*   Updated: 2019/03/19 11:43:05 by stdenis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <get_input.h>

char		*ft_update_hist(t_shell *sh)
{
	char	*ret;
	char	*hi_path;
	t_hist *hist;

	ret = ft_strdup(sh->e.hist->s);
	if (sh->e.hist->s[0] != '\0'
	&& (hi_path = get_tenvv_val(sh->env, "HISTORY")))
	{
		ft_write_in_file(hi_path, sh->e.hist->s);
		if (!sh->e.hist->prev)
			sh->hist = sh->e.hist;
		else
		{
			hist = sh->e.hist;
			while (hist->prev)
				hist = hist->prev;
			ft_strdel(&hist->s);
			hist->s = ft_strdup(sh->e.hist->s);
			sh->e.hist = hist;
			sh->hist = sh->e.hist;
		}
	}
	sh->e.mode = 1;
	ft_print_line(&sh->e);
	ft_set_old_term(sh);
	return (ret);
}

char		*get_input(void)
{
	t_shell			*sh;
	unsigned long	buf;

	sh = ft_get_set_shell(NULL);
	if (!isatty(0) || sh->interactive == FALSE || !init_tedit(sh))
		return (NULL);
	ft_setup_edit_term(sh);
	while (sh->e.edited == FALSE)
	{
		buf = 0;
		read(0, &buf, 8);
		buf = handle_input(buf, &sh->e);
		if (buf == 9)
		{
			return (NULL);
		}
		if (sh->hist)
			ft_print_line(&sh->e);
	}
	return (ft_update_hist(sh));
}
