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

struct	s_envv
{
	char	*name;
	char	*value;
	bool	exported;
	t_envv	*next;
};

t_envv	*ft_get_set_envv(t_envv *t);
t_envv	*ft_new_envv(t_envv *envv, char *name, char *value, bool exp);
t_envv	*ft_setenv(t_envv *envv, char **t, int mode, bool exp);
t_envv	*ft_unsetenv(t_envv *envv, char **t);
t_envv	*ft_del_envv(t_envv *envv, char *name);
int		ft_puttenvv(const t_envv *envv, bool exp);
t_envv	*del_tenvv(t_envv *envv);
t_envv	*ft_free_tenvv(t_envv *envv);
t_envv	*ft_pull_tenvv(t_envv *dest, const t_envv *src);
t_envv	*ft_push_tenvv(t_envv *dest, const t_envv *src);
t_envv	*new_tenvv(bool exp);
t_envv	*ft_changetenvv_val(t_envv *envv, char *name, char *new_val);
char	*get_tenvv_val(const t_envv *envv, char *name);
t_envv	*get_tenvv(t_envv *envv, char *name);
t_envv	*ft_tenvv_cpy(t_envv *src, bool exp);
char	**tenvv_to_tab(t_envv *envv);
t_envv	*ft_new_envv_equ(t_envv *envv, char *eq, bool exp);
t_envv	*ft_new_envv_int(t_envv *envv, char *name, int val, bool exp);

#endif
