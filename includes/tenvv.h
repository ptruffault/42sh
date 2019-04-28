/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tenvv.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adi-rosa <adi-rosa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/08 14:44:14 by adi-rosa          #+#    #+#             */
/*   Updated: 2019/04/24 16:08:34 by fstadelw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TENVV_H
# define TENVV_H

typedef struct s_envv	t_envv;

enum {
	EXP = 0x01,
	IN = 0x02,
	TMP = 0x04,
	NF = 0x08
};

struct	s_envv
{
	char	*name;
	char	*value;
	short	status;
	t_envv	*next;
};

#endif
