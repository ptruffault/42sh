/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adi-rosa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/18 15:33:46 by adi-rosa          #+#    #+#             */
/*   Updated: 2019/03/19 15:41:07 by stdenis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <shell42.h>


// PROBLEME DE FORGROUND pour 'cat &'

void	ft_disp(t_shell *sh)
{
	char *pwd;

	pwd = ft_update_pwd(sh);
	ft_putstr("\033[1;32m42sh\033[00m:[\033[01;34m\033[04m");
	ft_putstr(pwd);
	ft_putstr("\033[00m]\n");
}

int		ft_quit(int exit_code, t_shell *sh)
{
	kill_process(sh->process, SIGQUIT, RUNNING_FG);
	kill_process(sh->process, SIGQUIT, RUNNING_BG);
	kill_process(sh->process, SIGQUIT, SUSPENDED);
	ft_strdel(&sh->txt);
	ft_free_tshell(sh);
	return (exit_code);
}

int		main(int argc, char **argv, char **envv)
{
	t_shell	sh;
	t_tree	*t;
	char	*in;

	(void)argc;
	if (!init_shell(&sh, envv, argv))
		return (ft_quit(1, &sh));
	while (isatty(0))
	{
		ft_printf("1\n");
		ft_disp(&sh);
		if (!(get_input(&in)))
			return (ft_quit(1, &sh));
		if ((t = get_tree(in)))
			ft_free_tree(exec_tree(t, &sh));
		ft_strdel(&in);
	}
	ft_printf("stdin no longer tty\n");
	return (ft_quit(1, &sh));
}
