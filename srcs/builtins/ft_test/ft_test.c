/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_test.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stdenis <stdenis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/15 13:38:24 by stdenis           #+#    #+#             */
/*   Updated: 2019/03/17 18:34:45 by stdenis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell42.h"

static int		more_check_file(char **argv, struct stat *file)
{
	if (argv[0][1] == 'L' || argv[0][1] == 'h')
		return (S_ISLNK(file->st_mode) ? 0 : 1);
	if (argv[0][1] == 'p')
		return (S_ISFIFO(file->st_mode) ? 0 : 1);
	if (argv[0][1] == 'r')
		return ((file->st_mode & S_IRUSR) ? 0 : 1);
	if (argv[0][1] == 'S')
		return (S_ISSOCK(file->st_mode) ? 0 : 1);
	if (argv[0][1] == 's')
		return (file->st_size > 0 ? 0 : 1);
	if (argv[0][1] == 'u')
		return ((file->st_mode & S_ISUID) ? 0 : 1);
	if (argv[0][1] == 'w')
		return ((file->st_mode & S_IWUSR) ? 0 : 1);
	if (argv[0][1] == 'x')
		return ((file->st_mode & S_IXUSR) ? 0 : 1);
	return (2);
}

static int		check_arg_files(char **argv)
{
	struct stat	file;

	if (argv[1] == 0)
		return (0);
	else if (argv[1] != 0 && argv[2] != 0)
		return (return_fnc("test: too many arguments\n", 2));
	else if (argv[0][1] != '\0' && argv[0][2] != '\0')
		return (return_fnc("test: unknown condition:\n", 2));
	if (ft_strchr("bcdefghLprSsuwx", argv[0][1]) == NULL)
		return (return_fnc("test: unary operator expected\n", 2));
	if ((lstat(argv[1], &file)) < 0)
		return (1);
	if (argv[0][1] == 'b')
		return (S_ISBLK(file.st_mode) ? 0 : 1);
	if (argv[0][1] == 'c')
		return (S_ISCHR(file.st_mode) ? 0 : 1);
	if (argv[0][1] == 'd')
		return (S_ISDIR(file.st_mode) ? 0 : 1);
	if (argv[0][1] == 'e')
		return (0);
	if (argv[0][1] == 'f')
		return (S_ISREG(file.st_mode) ? 0 : 1);
	if (argv[0][1] == 'g')
		return ((file.st_mode & S_ISGID) ? 0 : 1);
	return (more_check_file(argv, &file));
}

static int		compare_argv(char **argv)
{
	if (argv[3] != 0)
		return (return_fnc("test: too many arguments\n", 2));
	if (check_integer_tab(argv[0]) || check_integer_tab(argv[2]))
		return (return_fnc("test: integer expression expected\n", 2));
	if (!(ft_strcmp(argv[1], "-eq")))
		return ((ft_atoi(argv[0]) == ft_atoi(argv[2]) ? 0 : 1));
	else if (!(ft_strcmp(argv[1], "-ne")))
		return ((ft_atoi(argv[0]) == ft_atoi(argv[2]) ? 1 : 0));
	else if (!(ft_strcmp(argv[1], "-gt")))
		return ((ft_atoi(argv[0]) > ft_atoi(argv[2]) ? 0 : 1));
	else if (!(ft_strcmp(argv[1], "-ge")))
		return ((ft_atoi(argv[0]) >= ft_atoi(argv[2]) ? 0 : 1));
	else if (!(ft_strcmp(argv[1], "-lt")))
		return ((ft_atoi(argv[0]) < ft_atoi(argv[2]) ? 0 : 1));
	else if (!(ft_strcmp(argv[1], "-le")))
		return ((ft_atoi(argv[0]) <= ft_atoi(argv[2]) ? 0 : 1));
	else
		return (return_fnc("test: unknown condition:\n", 2));
}

static int		test_builtin(char **argv)
{
	if (*argv && argv[0][0] == '-')
	{
		if (argv[0][1] == 'z')
			return ((argv[1] && ft_strlen(argv[1]) > 0) ? 0 : 1);
		else
			return (check_arg_files(argv));
	}
	else
	{
		if (*argv && argv[1] != 0 && argv[2] != 0)
			return (compare_argv(argv));
		else if (*argv && argv[1] != 0)
			return (return_fnc("test: parse error: condition expected.\n", 2));
	}
	return (0);
}

int				ft_test(char **argv)
{
	int		ret;

	ret = 1;
	if (argv[1])
	{
		if (argv[1][0] == '!' && argv[1][1] == '\0')
		{
			ret = test_builtin(&argv[2]);
			ret ^= 1;
		}
		else if (argv[1][0] != '!')
			ret = test_builtin(&argv[1]);
	}
	return (ret);
}
