/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tenvv_to_tab.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adi-rosa <adi-rosa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/05 13:42:31 by adi-rosa          #+#    #+#             */
/*   Updated: 2019/04/24 17:11:24 by fstadelw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "shell42.h"

static char			*get_equal(char *name, char *value)
{
	char	*tmp;
	char	*ret;

	ret = NULL;
	tmp = NULL;
	if (name && !(tmp = ft_strjoin(name, "=")))
		return (NULL);
	if (tmp && value)
		ret = ft_strjoin(tmp, value);
	ft_strdel(&tmp);
	return (ret);
}

static unsigned int	envv_len(t_envv *envv)
{
	unsigned int	i;

	i = 0;
	while (envv)
	{
		if (envv->status & EXP)
			i++;
		envv = envv->next;
	}
	return (i + 1);
}

char				**tenvv_to_tab(t_envv *envv)
{
	char	**t;
	int		i;

	i = 0;
	if (!envv || !(t = (char **)malloc(sizeof(char *) * envv_len(envv))))
		return (NULL);
	while (envv)
	{
		if ((envv->status & EXP) && (t[i] = get_equal(envv->name, envv->value)))
			i++;
		envv = envv->next;
	}
	t[i] = NULL;
	if (i == 0)
	{
		free(t);
		return (NULL);
	}
	return (t);
}

void				ft_get_envv_back(t_shell *sh, t_process *p, t_tree *t)
{
	if (t->ass)
	{
		if (p->saved_env)
		{
			sh->env = ft_restore_tenvv(sh->env, p->saved_env);
			p->saved_env = ft_free_tenvv(p->saved_env);
		}
		sh->env = ft_remove_tmp(sh->env);
	}
}

void				ft_setup_localenv(t_process *p, t_shell *sh, t_tree *t)
{
	if (t->ass)
	{
		if (sh->env)
			p->saved_env = ft_save_tenvv(sh->env, t->ass);
		sh->env = ft_push_tmp_env(sh->env, t->ass, (EXP | TMP));
	}
}
