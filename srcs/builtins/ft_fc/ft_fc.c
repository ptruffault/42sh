/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fc.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adi-rosa <adi-rosa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/29 14:47:53 by adi-rosa          #+#    #+#             */
/*   Updated: 2019/04/24 17:02:51 by fstadelw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "shell42.h"

static void		set_struct_fc(t_fc *fc, t_shell *shell)
{
	fc->shell = shell;
	fc->hist = shell->hist->next;
	fc->hist_first = NULL;
	fc->hist_last = NULL;
	fc->first = 0;
	fc->last = 0;
	fc->first_ = NULL;
	fc->last_ = NULL;
}

static int		init_fc(t_fc *fc, t_shell *shell, int *i, char **argv)
{
	fc->av = argv;
	if ((*i = flags_gestion(fc->flags, fc->av, -1)) == 1)
		return (2);
	if (fc->flags[0] != 'e' && (!shell->hist || !shell->hist->next))
	{
		if (shell->hist)
		{
			ft_strdel(&shell->hist->s);
			free(shell->hist);
			shell->hist = NULL;
		}
		return (1);
	}
	else if ((!shell->hist || !shell->hist->next))
	{
		if (shell->hist)
		{
			ft_strdel(&shell->hist->s);
			free(shell->hist);
			shell->hist = NULL;
		}
		return (0);
	}
	return (3);
}

static void		fc_init_first_last(t_fc *fc, int pos)
{
	if (fc->av[pos])
	{
		if ((ft_isdigit(fc->av[pos][0])) || fc->av[pos][0] == '-')
			fc->first = ft_atoi(fc->av[pos]) == 0 ? -1 : ft_atoi(fc->av[pos]);
		else
			fc->first_ = fc->av[pos];
		if (fc->av[pos + 1])
			if (ft_isdigit(fc->av[pos + 1][0]) || fc->av[pos + 1][0] == '-')
			{
				fc->last = ft_atoi(fc->av[pos + 1]);
				fc->last = (fc->last == 0) ? -1 : fc->last;
			}
			else
				fc->last_ = fc->av[pos + 1];
		else
			fc->last = -1;
	}
	else
	{
		fc->first = -1;
		fc->last = fc->flags[0] == 'e' ? -1 : -16;
		fc->first_ = NULL;
		fc->last_ = NULL;
	}
}

int				fc_delete_link(t_fc *fc, int x)
{
	if (fc->shell->hist && fc->shell->hist->next)
	{
		ft_strdel(&fc->shell->hist->s);
		fc->shell->hist = fc->shell->hist->next;
		free(fc->shell->hist->prev);
		fc->shell->hist->prev = NULL;
	}
	return (x);
}

int				ft_fc(t_shell *shell, char **argv)
{
	t_fc	fc;
	int		i;
	int		ret;

	if ((ret = init_fc(&fc, shell, &i, argv)) <= 2)
		return (ret);
	if (!shell->interactive)
		return (0);
	set_struct_fc(&fc, shell);
	if (fc.flags[0] == 'e' && fc.av[i]
		&& ft_isdigit(fc.av[i][0]) == 0 && fc.av[i][0] != '-')
		fc_init_first_last(&fc, i + 1);
	else if (fc.flags[0] == 's' && fc.av[i] && ft_strchr(fc.av[i], '='))
		fc_init_first_last(&fc, i + 1);
	else
		fc_init_first_last(&fc, i);
	if (fc.flags[0] == 'l' && ft_fc_option_l(&fc) == 1)
		return (1);
	else if (fc.flags[0] == 'e' && ft_fc_option_e(&fc, i) == 1)
		return (fc_delete_link(&fc, 1));
	else if (fc.flags[0] == 's' && ft_fc_option_s(&fc, i) == 1)
		return (fc_delete_link(&fc, 1));
	if (fc.flags[0] == 'e' || fc.flags[0] == 's')
		return (ft_atoi(get_tenvv_val(fc.shell->env, "?")));
	return (0);
}
