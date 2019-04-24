/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptruffau <ptruffau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/16 11:16:01 by ptruffau          #+#    #+#             */
/*   Updated: 2019/04/24 16:36:45 by fstadelw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stddef.h>
#include <fcntl.h>

# define BUFF_SIZE 256
# define FAILURE 0
# define SUCCESS 1

# define BLEUCLAIR 	"\x1B[01;34m"
# define ROUGE 		"\x1B[00;31m"
# define BLEU 		"\x1B[00;34m"
# define SOULIGNE 	"\x1B[04m"
# define NORMAL 	"\x1B[00m"
# define VERT  		"\x1B[1;32m"
# define CYAN 		"\x1B[1;36m"
# define MAGENTA 	"\x1B[1;35m"
# define JAUNE		"\x1B[1;39m"
# define S_ROUGE	"\x1b[1;34;41m"
# define S_BLEU		"\x1b[1;34;44m"
# define S_CYAN		"\x1b[1;36;46m"
# define S_ROSE		"\x1b[1;35;45m"
# define S_VERT		"\x1b[1;32;42m"

typedef enum	e_boolen {
	FALSE = 0,
	TRUE = 1
}				t_bool;

char	*ft_stradd(char **str, const char *end);
int		ft_open(const char *path, int flag, mode_t mode);
char	*ft_strchr_end(const char *src, char c);
int		ft_close(int fd);
int		warning(const char *descript, const char *opts);
int		error(const char *descript, const char *opts);
int		warning_c(const char *descript, char opts);
int		error_c(const char *descript, char opts);
int		error_i(const char *descript, int i);
char	*ft_strjoin_fr(char *s1, char *s2);
char	*ft_stradd_char(char *str, char c);
char	*ft_strnew_nchar(char c, int n);
char	*ft_strjoin_fr(char *s1, char *s2);
char	*ft_new_path(char *s1, char *s2);
int		get_next_line(const int fd, char **line);
void	ft_freestrarr(char ***arr);
char	**ft_delstrarr(char ***arr);
int		ft_str_startwith(const char *s1, const char *s2);
int		ft_str_endwith(const char *s1, const char *s2);
char	*ft_strpull(char *src, char *ptr, int len, char *value);
char	*ft_strndup(char *src, int len);
char	**ft_strsplit(char const *s, char c);
void	*ft_memcpy(void *dest, const void *src, size_t n);
void	*ft_memset(void *tampon, int car, size_t n);
size_t	ft_strlen(const char *s);
char	*ft_strdup(const char *s1);
char	*ft_strcpy(char *s1, const char *s2);
char	*ft_strncpy(char *s1, const char *s2, size_t n);
char	*ft_strcat(char *s1, const char *s2);
char	*ft_strncat(char *s1, const char *s2, size_t n);
size_t	ft_strlcat(char *dst, const char *src, size_t size);
char	*ft_strchr(const char *s, int c);
char	*ft_strrchr(const char *s, int c);
char	*ft_strstr(const char *s1, const char *s2);
char	*ft_strnstr(const char *s1, const char *s2, size_t n);
int		ft_strcmp(const char *s1, const char *s2);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
int		ft_ismaj(char c);
int		ft_ismin(char c);
int		ft_isalpha(int c);
int		ft_isdigit(int c);
int		ft_isequal(char *s);
int		ft_isequal_env(char *s);
int		ft_isempty(char *s);
int		ft_isspace(int c);
int		ft_isalnum(int c);
int		ft_isascii(int c);
int		ft_isprint(int c);
int		ft_toupper(int c);
int		ft_tolower(int c);
char	*ft_strnew(size_t size);
void	ft_strdel(char **as);
char	*ft_strdell(char **as);
int		ft_strequ(char const *s1, char const *s2);
int		ft_strnequ(char const *s1, char const *s2, size_t n);
char	*ft_strsub(char const *s, unsigned int start, size_t len);
char	*ft_strjoin(const char *s1, const char *s2);
char	**ft_strsplit(char const *s, char c);
char	*ft_get_prev_path(char *path);
int		ft_atoi(const char *str);
char	*ft_itoa(int n);
void	ft_putchar(char c);
void	ft_putstr(char const *s);
void	ft_putstrarr(char **t);
void	ft_putendl(char const *s);
void	ft_putnbr(int n);
void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char const *s, int fd);
void	ft_putendl_fd(char const *s, int fd);
void	ft_putnbr_fd(int n, int fd);
char	*ft_strjoin_add(char **s1, char **s2, const char *add);
char	*ft_strjoin_add_if(char **s1, char **s2, const char *add);
char	*ft_strappend(char **str, const char *end);
char	*ft_strappend_fr(char **str, char **end);
char	*ft_strinsert_char(char **str, char c, char *end);
char	*ft_strdup_trim(char *value);
char	*ft_strplexp(char *src, char *ptr, int len, char *value);
#endif
