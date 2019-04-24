/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stdenis <stdenis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/08 18:07:09 by stdenis           #+#    #+#             */
/*   Updated: 2019/04/24 17:14:44 by fstadelw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <stdbool.h>
# include <stdint.h>
# include <wchar.h>
# include "double.h"

enum {
	HASH = 0x01,
	PLUS = 0x02,
	MINUS = 0x04,
	ZERO = 0x08,
	SPACE = 0x10,
	PREC = 0x20,
	HH = 0x40,
	H = 0x80,
	LL = 0x100,
	L = 0x200,
	LDBL = 0x400,
	Z = 0x800,
	J = 0x1000
};

enum {
	C = 0,
	S = 1,
	P = 2,
	DI = 3,
	O = 4,
	U = 5,
	X = 6,
	XX = 7,
	F = 8,
	SS = 9,
	CC = 10,
	B = 11,
	PERCENT = 12
};

typedef uint16_t	t_flags;
typedef void		(*t_fnc[12])	(va_list ap, void *ptr);

typedef	struct		s_arg
{
	int		type;
	int		larg;
	int		prec;
	t_flags	flag;
}					t_arg;

typedef struct		s_printf
{
	t_arg	arg;
	size_t	fmt;
	size_t	buff;
	size_t	rtn;
	t_fnc	dispatcher;
	char	buffer[2048];
}					t_printf;

/*
** buffer.c
*/
void				fill_buffer(char c, t_printf *ptab);

/*
** arguments.c
*/
int					check_arg(const char *format, t_printf *ptab, va_list ap);

/*
** wild_char.c
*/
void				get_wild_char(t_printf *ptab, va_list ap);

/*
** string.c
*/
void				check_string(char *value, t_printf *ptab);
void				get_string(va_list ap, void *ptr);

/*
** char.c
*/
void				get_char(va_list ap, void *ptr);

/*
** integer.c
*/
void				check_integer(va_list ap, void *ptr);
void				check_unsigned_integer(va_list ap, void *ptr);
void				prepare_un(uintmax_t value, t_printf *ptab);

/*
** hexadecimal.c
*/
void				check_hexadecimal(va_list ap, void *ptr);

/*
** octal.c
*/
void				check_octal(va_list ap, void *ptr);

/*
** pointers.c
*/
void				get_pointers(va_list ap, void *ptr);

/*
** double.c
*/
void				check_float(va_list ap, void *ptr);

/*
** print_double.c
*/
void				print_flags_ldbl(t_dbl *tab_dbl, t_printf *ptab, char fill);
void				print_zero(t_printf *ptab, char fill, t_dbl *tab_dbl);

/*
** utils_double.c
*/
void				rounding_ldbl(t_dbl *tab_dbl, t_printf *ptab);
void				repos_pointers(t_dbl *tab_dbl, uint32_t last, int decal);
void				calculate_nbr_integer(t_dbl *tab_dbl);
void				print_others(t_dbl *tab_dbl, int check, t_printf *ptab);

/*
** transform_ldbl.c
*/
void				transform_ldbl_80b(t_dbl *tab_dbl, t_printf *ptab);

/*
** ft_putnbrs.c
*/
void				putnbr_p(uintmax_t res, t_printf *ptab);
void				putnbr_n(intmax_t res, t_printf *ptab);
void				putnbr_c(uintmax_t res, t_printf *ptab, char *base, int bl);
bool				check_flags(t_flags flag, int m, t_flags f, t_flags s);
int					uint_length(uintmax_t value, int base);

/*
** ft_printf.c
*/
int					ft_printf(const char *format, ...);

/*
** unicode.c
*/
void				get_char_uni(va_list ap, void *ptr);
void				get_string_uni(va_list ap, void *ptr);

/*
** binary.c
*/
void				check_binary(va_list ap, void *ptr);

/*
** utils_unicode.c
*/

size_t				len_octects(const wchar_t c);
size_t				ft_strlen_unicode(const wchar_t *str, t_printf *ptab);

/*
** utils.c
*/
void				*ft_memset(void *b, int c, size_t n);
size_t				ft_strlen(const char *str);
int					get_size_flag(t_printf *ptab, const char *str, int prec);
int					int_length(intmax_t value, int base);
void				rounding_prec_zero(t_dbl *tab_dbl, t_printf *ptab);

#endif
