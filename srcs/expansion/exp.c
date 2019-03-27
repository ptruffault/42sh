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

char	*get_last_process_val(t_process *p, int mode)
{
	while (p)
	{
		if (!mode && p->status == DONE)
			return (ft_itoa(p->ret));
		if (mode && p->background == TRUE)
			return (ft_itoa(p->pid));
		p = p->next;
	}
	return (NULL);
}

char		*ft_exp_spec(char *ret, char *ptr, t_shell *sh)
{
	char		*val;

	val = NULL;
	if ((ptr[1] == '!' || ptr[1] == '?') && sh->process)
		val = get_last_process_val(sh->process, (ptr[1] == '?' ? 0 : 1));
	if (ptr[1] == '$')
		val = ft_itoa(sh->pid);
	if (!(ptr = ft_strpull(ret, ptr, 1, val)))
	{
		ft_strdel(&val);
		return (ret);
	}
	ft_strdel(&ret);
	return (ptr);
}

char		*ft_exp_var(char *ret, t_shell *sh)
{
	int i;

	i = 0;
	while (ret && *ret && ret[i])
	{
		if ((ret && ret[i] == '~'
		&& !(ret = ft_exp_home_var(ret, &ret[i], sh->env)))
		|| (ret && ret[i] == '$' && ret[i + 1] == '{'
		&& !(ret = ft_exp_param(ret, sh, &ret[i])))
		|| (ret && ret[i] == '$' && ret[i + 1] && ft_strchr("$!?", ret[i + 1])
		&& !(ret = ft_exp_spec(ret, &ret[i], sh)))
		|| (ret && ret[i] == '$' && ret[i + 1] && !ft_strchr("$!?{", ret[i + 1])
		&& !(ret = ft_exp_envv_var(ret, &ret[i], sh))))
			return (NULL);
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
