/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adi-rosa <adi-rosa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/29 11:57:43 by adi-rosa          #+#    #+#             */
/*   Updated: 2019/04/24 16:20:55 by fstadelw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/ioctl.h>
#include "shell42.h"
#include "get_input.h"

static void	setup_key(char *error[7], t_edit *e)
{
	error[0] = "\ncmdand";
	error[1] = "\ncmdor";
	error[2] = "\npipe";
	error[3] = "\nquote";
	error[4] = "\ndquote";
	error[5] = "\nbackslash";
	error[6] = "\nparenth";
	if (e->tmp == NULL)
		e->tmp = e->hist->s;
	else
		e->tmp = ft_strjoin_fr(e->tmp, e->hist->s);
	e->hist->s = e->tmp;
}

int			check_eval(char *str)
{
	char	*tmp;

	tmp = str;
	while ((tmp = ft_strchr(tmp, 'o')))
	{
		if (ft_strchr(tmp + 1, 'o') - tmp + 1 == 3)
			return (0);
		if (ft_strstr(tmp + 1, "oo") - tmp + 1 == 4)
			return (0);
		tmp++;
	}
	tmp = str;
	while ((tmp = ft_strstr(tmp, "oo")))
	{
		if (ft_strstr(tmp + 1, "oo") - tmp + 1 == 4)
			return (0);
		if (ft_strchr(tmp + 1, 'o') - tmp + 1 == 3)
			return (0);
		tmp++;
	}
	return (1);
}

void		entry_key(t_edit *e)
{
	t_eval	eval;
	t_shell	*sh;
	char	*error[7];

	if (e->mode == 2 && ft_incr_add(e) == SUCCESS)
		return ;
	sh = ft_get_set_shell(NULL);
	setup_key(error, e);
	lexer(&eval, e->hist->s);
	if (eval.eval != NULL && check_eval(eval.eval)
		&& sh->heredoc == 0 && eval.err > 1)
	{
		reset_tedit(e);
		eval.err = (eval.err >= 2) ? eval.err - 2 : eval.err;
		e->tmp = ft_strjoin_add_edit(&e->tmp, "\n", eval.err);
		ft_others_prompt(ft_get_set_shell(NULL), error[eval.err]);
	}
	else
	{
		e->tmp = NULL;
		e->edited = TRUE;
		if (sh->heredoc == 0 && check_for_hist_exp(e) == SUCCESS)
			e->edited = FALSE;
	}
	ft_strdel(&eval.eval);
	ft_strdel(&eval.s);
}
