/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adi-rosa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/08 14:21:33 by adi-rosa          #+#    #+#             */
/*   Updated: 2019/03/26 17:21:55 by stdenis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell42.h"
#include "ft_printf.h"

static void	ft_lex_redirect(t_eval *e)
{
	int	j;

	j = e->curr;
	while (j > 0 && ft_isdigit(e->s[j - 1]))
		e->eval[--j] = 'r';
	while (e->s[e->curr] == '<' || e->s[e->curr] == '>')
		e->eval[e->curr++] = 'r';
	if (e->s[e->curr] && e->s[e->curr] == '&')
	{
		e->eval[e->curr++] = 'r';
		if (e->s[e->curr] == '-')
			e->eval[e->curr++] = 'r';
		else if (e->s[e->curr] && ft_isdigit(e->s[e->curr]))
			while (ft_isdigit(e->s[e->curr]))
				e->eval[e->curr++] = 'r';
		else if (e->s[e->curr])
			while (e->s[e->curr] && !ft_isspace(e->s[e->curr]))
				e->eval[e->curr++] = 'r';
	}
}

static void	ft_lex_operateur(t_eval *e)
{
	int	i;

	e->c = e->s[e->curr];
	i = 0;
	e->eval[e->curr++] = 'o';
	if (e->s[e->curr] && e->s[e->curr] == e->c)
	{
		i = 1;
		e->eval[e->curr++] = 'o';
	}
	if (e->c != ';' && !(e->c == '&' && i == 0)
		&& (!e->s[e->curr] || ft_isempty(&e->s[e->curr])))
	{
		if (e->c == '|' && i == 0)
			e->err = OP_MISS;
		else if (e->c == '|')
			e->err = OO_MISS;
		else
			e->err = OA_MISS;
	}
	if (e->s[e->curr] != e->c && (e->s[e->curr] == '&'
			|| e->s[e->curr] == '|' || e->s[e->curr] == ';'))
		e->err = SYNTAX;
}

void		ft_lex_var(t_eval *e)
{
	e->eval[e->curr++] = 'v';
	while (e->s[e->curr] && !ft_isspace(e->s[e->curr]))
	{
		if (e->s[e->curr] == '{')
			ft_lex_parenth(e);
		else
			e->eval[e->curr++] = 'v';
	}
}

static void	ft_lexword(t_eval *e)
{
	while (ft_isspace(e->s[e->curr]))
		e->eval[e->curr++] = ' ';
	if (!e->s[e->curr])
		return ;
	else if (e->s[e->curr] && e->s[e->curr] == '"')
		ft_lex_dquote(e);
	else if (e->s[e->curr] && e->s[e->curr] == '\'')
		ft_lex_quote(e);
	else if (e->s[e->curr] && e->s[e->curr] == '\\')
		ft_lex_backslash(e);
	else if (e->s[e->curr] && (ft_strchr("<>", e->s[e->curr])))
		ft_lex_redirect(e);
	else if (e->s[e->curr] && (ft_strchr("&|;", e->s[e->curr])))
		ft_lex_operateur(e);
	else if (e->s[e->curr] && e->s[e->curr] == '$')
		ft_lex_var(e);
	else if (e->s[e->curr] && e->s[e->curr] == '{')
		ft_lex_parenth(e);
	else if (e->s[e->curr])
		e->eval[e->curr++] = 'e';
}

void		lexer(t_eval *e, char *src)
{
	e->curr = 0;
	e->err = OK;
	e->eval = NULL;
	e->s = NULL;
	if ((e->s = ft_strdup(src)))
	{
		if ((e->eval = ft_strnew(ft_strlen(e->s))))
		{
			while (e->s[e->curr])
				ft_lexword(e);
			e->eval[e->curr] = 0;
		}
		else
			ft_strdel(&e->s);
	}
}
