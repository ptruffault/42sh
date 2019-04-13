/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adi-rosa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/08 14:44:14 by adi-rosa          #+#    #+#             */
/*   Updated: 2019/03/26 16:47:28 by stdenis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TENVV_H
# define TENVV_H
# include <stdbool.h>
# include "libft.h"

typedef struct s_envv	t_envv;

enum {
	EXP = 0x01,
	IN = 0x02,
	TMP = 0x04,
};

struct	s_envv
{
	char	*name;
	char	*value;
	short	status;
	t_envv	*next;
};

char	*ft_split_equal(char *str, char **aft);
t_envv	*ft_get_set_envv(t_envv *t);
t_envv	*ft_new_envv(t_envv *envv, const char *name, const char *value, short status);
t_envv	*ft_setenv(t_envv *envv, char **t, int mode, short status);
t_envv	*ft_unsetenv(t_envv *envv, char **t);
t_envv	*ft_del_envv(t_envv *envv, char *name);
int		ft_puttenvv(t_envv *envv, short status);
t_envv	*del_tenvv(t_envv *envv);
t_envv	*ft_free_tenvv(t_envv *envv);
t_envv	*ft_push_tenvv(t_envv *dest, const t_envv *src, short status);
t_envv	*new_tenvv(short status);
t_envv	*ft_changetenvv_val(t_envv *envv, const char *name, const char *new_val);
char	*get_tenvv_val(t_envv *envv, const char *name);
t_envv	*get_tenvv(t_envv *envv, const char *name);
char	**tenvv_to_tab(t_envv *envv);
t_envv	*ft_new_envv_equ(t_envv *envv, char *eq,  short status);
t_envv	*ft_new_envv_int(t_envv *envv, const char *name, int val, short status);
t_envv	*ft_remove_tmp(t_envv *dest);
t_envv	*ft_save_tenvv(t_envv *org, t_envv *tmp);
#endif
