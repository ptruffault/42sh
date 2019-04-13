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

#endif
