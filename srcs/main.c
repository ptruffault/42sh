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

static const char	*g_colors[] = {
	BLEUCLAIR,
	ROUGE,
	BLEU,
	SOULIGNE,
	NORMAL,
	VERT,
	CYAN,
	MAGENTA,
	JAUNE,
	"\0",
};

static char	*ft_replace_home(char *path, char *home)
{
	char	*tmp;

	if (!home || !path)
		return (path);
	if (!(tmp = ft_strstr(path, home)))
		return (path);
	path[0] = '~';
	ft_strcpy(path + 1, tmp + ft_strlen(home));
	return (path);
}

void		ft_print_colors(char *str, int *ptr)
{
	int					i;
	const char *const	colors[] = {
			"BLUE", "RED", "BLUE2", "UNDERLINE", "RESET",
			"GREEN", "CYAN", "MAGENTA", "YELLOW", "\0"
	};

	i = 0;
	while (str[i] != ']' && str[i] != '\0')
		i += 1;
	if (str[i] == '\0')
		*ptr += i;
	else
		*ptr += i + 1;
	str[i] = '\0';
	i = -1;
	while (colors[++i][0] != '\0')
		if (ft_strequ(colors[i], str + 2))
			break ;
	ft_putstr(g_colors[i]);
}

void		ft_print_var(t_shell *sh, char *str, int *ptr)
{
	int		i;
	char	*val;

	i = 0;
	val = NULL;
	while (str[i] != '}' && str[i] != '\0')
		i += 1;
	if (str[i] == '\0')
		*ptr += i;
	else
		*ptr += i + 1;
	str[i] = '\0';
	if ((val = ft_strdup(get_tenvv_val(sh->env, str + 2))))
	{
		if (ft_strequ("PWD", str + 2))
			val = ft_replace_home(val, get_tenvv_val(sh->env, "HOME"));
		ft_putstr(val);
	}
	else if ((val = ft_strdup(get_tenvv_val(sh->env, str + 2))))
		ft_putstr(val);
	ft_strdel(&val);
}

void		ft_disp(t_shell *sh)
{
	int		i;
	char	*prompt;

	if ((prompt = ft_strdup(get_tenvv_val(sh->env, "PS1"))))
	{
		i = 0;
		while (prompt[i])
		{
			if (prompt[i] == '$' && prompt[i + 1] == '[')
				ft_print_colors(&prompt[i], &i);
			else if (prompt[i] == '$' && prompt[i + 1] == '{')
				ft_print_var(sh, &prompt[i], &i);
			else
				ft_putchar(prompt[i++]);
		}
		ft_putchar('\n');
		ft_strdel(&prompt);
	}
	else
		ft_putendl("&>");
}

int			main(int argc, char **argv, char **envv)
{
	t_shell	sh;
	t_tree	*t;

	(void)argc;
	if (!init_shell(&sh, envv, argv))
		return (ft_quit(1, &sh));
	while (isatty(STDIN_FILENO) && isatty(STDOUT_FILENO))
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
