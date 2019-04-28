/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptruffau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/08 15:28:34 by ptruffau          #+#    #+#             */
/*   Updated: 2019/03/26 17:21:55 by stdenis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell42.h"

int		ft_check_in_head(char **head, char *str, int loop)
{
	char	*node;
	int		size;

	size = -1;
	if (!head)
		return (1);
	while (++size <= loop)
	{
		node = head[size];
		if (ft_strequ(node, str))
		{
			return (0);
		}
	}
	return (1);
}

void	ft_lex_backslash(t_eval *e)
{
	ft_delete_char(e);
	if (e->s[e->curr])
		e->eval[e->curr++] = 'B';
	else
	{
		e->err = B_MISS;
		e->c = '\\';
		return ;
	}
}

void	ft_lex_parenth(t_eval *e)
{
	while (e->s[e->curr] && e->s[e->curr] != '}')
	{
		e->eval[e->curr++] = 'v';
		if (e->s[e->curr] == '{')
			ft_lex_parenth(e);
	}
	if (!e->s[e->curr] || (e->s[e->curr] == '}' && e->s[e->curr - 1] == '\\'
		&& e->s[e->curr - 2] != '\\'))
	{
		e->err = P_MISS;
		e->c = '{';
	}
	else
		e->eval[e->curr++] = 'v';
}

void	ft_lex_dquote(t_eval *e)
{
	e->eval[e->curr++] = '*';
	if (e->s[e->curr] == '"')
	{
		e->s[e->curr] = ' ';
		e->eval[e->curr++] = '*';
	}
	else
	{
		while (e->s[e->curr] && e->s[e->curr] != '"')
		{
			if (e->s[e->curr] == '\\' && e->s[e->curr + 1])
				e->eval[e->curr++] = 'q';
			e->eval[e->curr++] = 'q';
		}
		if (!e->s[e->curr])
		{
			e->err = DQ_MISS;
			e->c = '"';
		}
		else
			e->eval[e->curr++] = '*';
	}
}

void	ft_lex_quote(t_eval *e)
{
	e->eval[e->curr++] = '*';
	if (e->s[e->curr] == '\'')
	{
		e->s[e->curr] = ' ';
		e->eval[e->curr++] = '*';
	}
	else
	{
		while (e->s[e->curr] != 0 && e->s[e->curr] != '\'')
			e->eval[e->curr++] = 's';
		if (!e->s[e->curr])
		{
			e->err = Q_MISS;
			e->c = '\'';
		}
		else
			e->eval[e->curr++] = '*';
	}
}
