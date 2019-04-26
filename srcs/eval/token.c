/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c.                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptruffau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/07 14:19:48 by ptruffau          #+#    #+#             */
/*   Updated: 2019/03/26 17:21:55 by stdenis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell42.h"

static t_word	*find_type(t_word *w, char c, int *pos)
{
	if (c == 'o')
		w->type = OPERATEUR;
	else if (c == 'r')
		w->type = REDIRECT;
	else if (c == 'q')
		w->type = DQUOTE;
	else if (c == 's' || c == 'B')
		w->type = QUOTE;
	else if (c == 'e' || c == '.' || c == 'v')
	{
		if (*pos == 0 && c != 'v')
			w->type = CMD;
		else
			w->type = ARG;
		*pos = *pos + 1;
	}
	else if (c == '*')
		w->type = NUL;
	else
		w->type = 0;
	return (w);
}

static t_word	*g_n_w(t_word *w, t_eval *e, int *i, int *pos)
{
	int begin;

	begin = *i;
	if (e->eval[begin] == '*')
		*i = ++begin;
	while (e->eval[*i] && e->eval[*i] == e->eval[begin])
		*i = *i + 1;
	if (e->eval[begin] != '*'
		&& !(w->word = ft_strndup(&e->s[begin], *i - begin)))
		return (NULL);
	if (e->eval[begin] == '*' && !(w->word = ft_strdup("@")))
		return (NULL);
	while (e->eval[*i] == '*')
		*i = *i + 1;
	if (!ft_strchr("or ", e->eval[*i]))
		w->paste = TRUE;
	return (find_type(w, e->eval[begin], pos));
}

t_word			*ft_get_words(t_eval *e)
{
	t_word	*head;
	t_word	*tmp_w;
	int		pos;
	int		i;
	int		len;

	i = 0;
	pos = 0;
	if (!(head = new_tword()))
		return (NULL);
	len = (int)ft_strlen(e->s);
	tmp_w = head;
	while (e->eval && i < len && e->eval[i] != '\0')
	{
		while (e->eval[i] && e->eval[i] == ' ')
			i++;
		if (e->eval[i] && !(tmp_w = g_n_w(tmp_w, e, &i, &pos)))
			return (ft_free_tword(head));
		if (e->eval && e->eval[i] && !(tmp_w->next = new_tword()))
			return (ft_free_tword(head));
		tmp_w = tmp_w->next;
	}
	return (head);
}

t_word			*eval_line(char *input)
{
	t_word	*head;
	t_eval	e;
	t_shell	*sh;

	sh = ft_get_set_shell(NULL);
	head = NULL;
	if (!input || !*input || ft_isempty(input))
		return (NULL);
	lexer(&e, input);
	if (e.s && e.eval && (head = ft_get_words(&e))
		&& !(head = ft_check_alias(head, sh, 0)))
	{
		ft_strdel(&e.eval);
		ft_strdel(&e.s);
		return (ft_free_tword(head));
	}
	ft_strdel(&e.eval);
	ft_strdel(&e.s);
	return (head);
}
