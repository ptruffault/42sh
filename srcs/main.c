/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adi-rosa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/18 15:33:46 by adi-rosa          #+#    #+#             */
/*   Updated: 2019/03/20 18:11:13 by stdenis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <shell42.h>

// compar getpgrp with the foreground process on term (tcgetpgrp)
// |-> le shell a été lancer depuis un autre shell qui gere le job control
// |-> le shell es en background (interactif = SIGGTTIN)
// 
// Job control is now available
// setpgid() -> set 42sh in it's own group
//  |-> tcsetpgrp to place his group in term forground
//  |-> NIK SA MER
//
// 


void	ft_disp(t_shell *sh)
{
	char *pwd;

	pwd = ft_update_pwd(sh);
	ft_putstr("\033[1;32m42sh\033[00m:[\033[01;34m\033[04m");
	ft_putstr(pwd);
	ft_putstr("\033[00m]\n");
}

int		main(int argc, char **argv, char **envv)
{
	t_shell	sh;
	t_tree	*t;

	(void)argc;
	if (!init_shell(&sh, envv, argv))
		return (ft_quit(1, &sh));
	while (isatty(0))
	{
		ft_disp(&sh);
		if (!(get_input(&sh.txt)))
			return (ft_quit(1, &sh));
		if ((t = get_tree(sh.txt)))
			ft_free_tree(exec_tree(t, &sh));
		ft_strdel(&sh.txt);
	}
	ft_printf("stdin no longer tty\n");
	return (ft_quit(1, &sh));
}
