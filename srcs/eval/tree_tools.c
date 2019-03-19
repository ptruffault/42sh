/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_tools.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptruffau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/08 15:30:54 by ptruffau          #+#    #+#             */
/*   Updated: 2019/03/19 19:04:57 by stdenis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <shell42.h>

int			ft_check_ascii(char *input)
{
	int i;

	i = 0;
	while (input[i])
		if (!ft_isascii(input[i++]))
			return (0);
	return (1);
}

t_tree		*new_tree(void)
{
	t_tree	*n;

	if (!(n = (t_tree *)malloc(sizeof(t_tree))))
		return (NULL);
	n->cmd = NULL;
	n->r = NULL;
	n->o_type = 0;
	n->ret = 0;
	n->next = NULL;
	return (n);
}

t_redirect	*new_redirection(void)
{
	t_redirect	*ret;

	if (!(ret = (t_redirect *)malloc(sizeof(t_redirect))))
		return (NULL);
	ret->t = 0;
	ret->to = -2;
	ret->from = -2;
	ret->path = NULL;
	ret->heredoc = NULL;
	ret->next = NULL;
	return (ret);
}

static int	find_operateur(char *op)
{
	char	*operateur[5];
	int		i;

	operateur[0] = "&&";
	operateur[1] = "||";
	operateur[2] = ";";
	operateur[3] = "|";
	operateur[4] = "&";
	i = 0;
	while (i < 5)
		if (ft_strequ(operateur[i++], op))
			return (i);
	return (0);
}

t_tree		*add_newttree(t_tree *tree, t_word *w)
{
	tree->o_type = find_operateur(w->word);
	if (w->type != 0)
	{
		if (!(tree->next = new_tree()))
			return (NULL);
		w = w->next;
	}
	return (tree->next);
}
