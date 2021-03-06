/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_type.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptruffau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/08 12:35:47 by ptruffau          #+#    #+#             */
/*   Updated: 2019/03/26 17:21:55 by stdenis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell42.h"

static t_word	*init_opts(char opts[4], t_word *w)
{
	int i;

	while (w && w->word && *w->word == '-')
	{
		i = 0;
		if (w->word[1] == '-')
			return (w->next);
		while (w->word[++i])
			if (ft_strchr("atpP", w->word[i]))
			{
				opts[0] = (w->word[i] == 'a' ? 1 : opts[0]);
				opts[1] = (w->word[i] == 't' ? 1 : opts[1]);
				opts[2] = (w->word[i] == 'p' ? 1 : opts[2]);
				opts[3] = (w->word[i] == 'P' ? 1 : opts[3]);
			}
			else
			{
				error_c("type: bad option :", w->word[i]);
				ft_putendl_fd("usage: type [-aptP] name [name ...]", 2);
				return (NULL);
			}
		w = w->next;
	}
	return (w);
}

static int		handle_opts(t_word *w, char opts[4], t_shell *sh)
{
	int ret;

	ret = 0;
	if (opts[3] == 1)
		return (putfile(w, sh->env, opts[1]));
	else if (opts[2] == 1)
		return (putcmd(w, sh->env, opts[1]));
	else if (opts[0] == 1)
	{
		ret = ret + putword(w, opts[1]);
		ret = ret + putalias(w, sh->alias, opts[1]);
		ret = ret + putbuiltin(w, opts[1]);
		ret = ret + putfile(w, sh->env, opts[1]);
		ret = ret + putcmd(w, sh->env, opts[1]);
		return (ret);
	}
	else if (!putword(w, opts[1]) && !putalias(w, sh->alias, opts[1])
		&& !putbuiltin(w, opts[1]) && !putfile(w, sh->env, opts[1])
		&& !putcmd(w, sh->env, opts[1]))
		return (0);
	return (1);
}

int				ft_type(t_word *w)
{
	t_shell	*sh;
	int		ret;
	char	opts[4];

	ft_memset(opts, 0, 4);
	if (!w || !w->word)
		return (0);
	if (!(w = init_opts(opts, w)))
		return (2);
	ret = 0;
	sh = ft_get_set_shell(NULL);
	while (w)
	{
		if (w->word && !handle_opts(w, opts, sh))
		{
			ret = 1;
			warning("not found", w->word);
		}
		w = w->next;
	}
	return (ret);
}
