/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adi-rosa <adi-rosa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/18 15:33:46 by adi-rosa          #+#    #+#             */
/*   Updated: 2019/04/24 17:16:38 by fstadelw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "shell42.h"
#include "ft_printf.h"

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
	error("shell no longer connected to terminal", NULL);
	return (ft_quit(1, &sh));
}
