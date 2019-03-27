/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   double.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stdenis <stdenis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/04 12:53:48 by stdenis           #+#    #+#             */
/*   Updated: 2019/03/08 14:42:35 by stdenis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DOUBLE_H
# define DOUBLE_H

# include <stdint.h>

typedef union		u_uniondbl
{
	long double		val;
	struct			s_binary
	{
		unsigned	mantissa2 : 32;
		unsigned	mantissa1 : 32;
		unsigned	exponent : 15;
		unsigned	sign : 1;
		unsigned	empty : 16;
	}				t_binary;
}					t_uniondbl;

typedef union		u_binary
{
	long double		val;
	struct			s_bits
	{
		uint64_t	mantissa;
		uint16_t	exposign;
	}				t_bits;
}					t_binary;

typedef struct		s_dbl
{
	double			dbl;
	long double		ldbl;
	int				integer;
	int				sign;
	uint32_t		rounding;
	uint32_t		numbers[2000];
	uint32_t		*head;
	uint32_t		*last;
	uint32_t		*before_dot;
	uint32_t		*digits;
}					t_dbl;

#endif
