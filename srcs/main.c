/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adi-rosa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/18 15:33:46 by adi-rosa          #+#    #+#             */
/*   Updated: 2019/03/19 11:42:21 by stdenis          ###   ########.fr       */
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

int		main(int argc, char **argv, char **envv)
{
	t_shell	sh;
	t_tree	*t;
	char	*in;

	(void)argc;
	init_shell(&sh, envv, argv);
	while (42 && isatty(0))
	{
		ft_disp(&sh);
		in = get_input();
		if ((t = get_tree(in)))
			ft_free_tree(exec_tree(t, &sh));
		ft_strdel(&in);
	}
	ft_printf("stdin no longer tty\n");
	ft_exit("42", &sh);
	return (0);
}
