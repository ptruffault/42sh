/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adi-rosa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/18 15:33:46 by adi-rosa          #+#    #+#             */
/*   Updated: 2019/03/26 17:18:36 by stdenis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell42.h"

int			main(int argc, char **argv, char **envv)
{
	t_shell	sh;
	t_tree	*t;

	(void)argc;
	if (!init_shell(&sh, envv, argv))
		return (ft_quit(226, &sh));
	while (isatty(STDIN_FILENO))
	{
		sh.err = 0;
		ft_disp(&sh);
		if (!(get_input(&sh.txt)))
			return (ft_quit(226, &sh));
		if ((t = get_tree(sh.txt, &sh)))
			ft_free_tree(exec_tree(t, &sh));
		ft_strdel(&sh.txt);
		ft_wait_background(&sh);
	}
	ft_printf("stdin no longer tty\n");
	return (ft_quit(1, &sh));
}
