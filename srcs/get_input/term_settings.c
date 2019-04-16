/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adi-rosa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/05 12:32:55 by adi-rosa          #+#    #+#             */
/*   Updated: 2019/03/26 17:21:55 by stdenis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <get_input.h>

void	ft_update_windows(t_edit *e, bool print)
{
	struct winsize	window;

	if ((ioctl(0, TIOCGWINSZ, &window)) == 0)
	{
		e->width = window.ws_col;
		e->tall = window.ws_row;
		e->max_char = (e->width * (e->tall - 1));
		if (print)
		{
			ft_delete_line(e);
			curr_go_last(e);
			if (e->pos_z > 0 || e->pos_y > 0)
				ft_disp(ft_get_set_shell(NULL));
			ft_print_fast(e);
		}
	}
	else
	{
		e->width = 6;
		e->tall = 2;
	}
}

int		init_termcaps(t_shell *sh)
{
	char *term;

	term = NULL;
	if (!(term = get_tenvv_val(sh->env, "TERM")))
		return (error("unset var", "TERM"));
	if (((term = get_tenvv_val(sh->env, "TERM")) && !tgetent(NULL, term)))
		return (error("can't retrieve terminal informations", term));
	if (!get_tgetstr("ch", NULL) || !get_tgetstr("cd", NULL)
		|| !get_tgetstr("up", NULL))
		return (error("term doesn't support necassary termcaps", term));
	if (tcgetattr(0, &sh->saved_term) == -1)
		return (error("can't save termios", term));
	ft_update_windows(&sh->e, false);
	return (1);
}

int		ft_setup_edit_term(t_shell *sh)
{
	char			*term;
	unsigned long	set;

	term = NULL;
	if (((term = get_tenvv_val(sh->env, "TERM")) && !tgetent(NULL, term)))
		return (error("can't retrieve terminal informations", term));
	if (!(tgetstr("ch", NULL))
		|| !(tgetstr("cd", NULL)) || !(tgetstr("up", NULL)))
		return (error("term doesn't support necassary termcaps", term));
	ft_memcpy(&sh->term, &sh->saved_term, sizeof(struct termios));
	set = ICANON | ECHO | ECHOK | ECHOKE | ECHONL | ECHOCTL | ISIG;
	sh->term.c_lflag &= ~(set);
	sh->term.c_cc[VMIN] = 1;
	sh->term.c_cc[VTIME] = 0;
	sh->term.c_cc[VINTR] = 3;
	sh->term.c_cc[VEOF] = 4;
	if ((tcsetattr(0, TCSADRAIN, &sh->term)) == -1)
		return (0);
	return (1);
}

int		ft_set_old_term(t_shell *sh, int error)
{
	if ((tcsetattr(0, TCSADRAIN, &sh->saved_term)) == -1)
		warning("can't load old term setting", NULL);
	term_actions("ve");
	return (error);
}
