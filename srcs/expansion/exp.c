/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expention.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptruffau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/08 16:10:38 by ptruffau          #+#    #+#             */
/*   Updated: 2019/03/26 17:21:55 by stdenis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell42.h"

char		*ft_exp_var(char *ret, t_shell *sh)
{
	int i;

	i = 0;
	while (ret && *ret && ret[i])
	{
				ft_printf("exp loop ~> %s\n", ret);
		if ((i == 0 || ret[i - 1] != '\\')
		&& ((ret && ret[i] == '~'
		&& !(ret = ft_exp_home_var(ret, &ret[i], sh->env)))
		|| (ret && ret[i] == '$' && ret[i + 1] == '{'
		&& !(ret = ft_exp_param(ret, sh, &i)))
		|| (ret && ret[i] == '$' && ret[i + 1] != '{'
		&& !(ret = ft_exp_envv_var(ret, &ret[i], sh)))))
			return (NULL);
		if (ret[i] != '$' && ret[i] != '~')
			i++;
	}
	return (ret);
}

t_word		*ft_expention(t_word *w)
{
	t_shell	*sh;
	t_word	*head;

	head = w;
	if (!(sh = ft_get_set_shell(NULL)))
		return (head);
	while (w)
	{
		if (IS_EXP(w->type) && w->word)
			w->word = ft_exp_var(w->word, sh);
		w = w->next;
	}
	return (head);
}
