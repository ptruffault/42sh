/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structures.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptruffau <ptruffau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/07 16:16:37 by ptruffau          #+#    #+#             */
/*   Updated: 2019/04/24 16:08:08 by fstadelw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTURES_H
# define STRUCTURES_H
# include <term.h>
# include "tenvv.h"

# define FCTMP "/tmp/fc____42sh"
# define FCTMPEXEC " /tmp/fc____42sh"
# define NUMBER_OF_KEYS 25
# define NUMBER_OF_PRINT_MODES 3
# define HASHTABLE_SIZE 150
# define OPEN_OPTION O_NOFOLLOW | O_NONBLOCK

enum	e_rtype{
	UNDEF = 0,
	R_LEFT = 1,
	R_RIGHT = 2,
	R_DLEFT = 3,
	R_DRIGHT = 4
};

enum	e_otype{
	UN = 0,
	O_AND = 1,
	O_OR = 2,
	O_SEP = 3,
	O_PIPE = 4,
	O_BACK = 5
};

enum	e_wtype{
	undef = 0,
	CMD = 1,
	ARG = 2,
	DQUOTE = 3,
	QUOTE = 4,
	REDIRECT = 5,
	OPERATEUR = 6,
	NUL = 7
};

enum	e_pstatus{
	INIT = 0,
	RUNNING_FG = 1,
	RUNNING_BG = 2,
	DONE = 3,
	SUSPENDED = 4,
	KILLED = 5
};

enum	e_error
{
	OK = 0,
	SYNTAX = 1,
	OA_MISS = 2,
	OO_MISS = 3,
	OP_MISS = 4,
	Q_MISS = 5,
	DQ_MISS = 6,
	B_MISS = 7,
	P_MISS = 8
};

union					u_str
{
	unsigned long		buff;
	unsigned char		str[9];
};

typedef unsigned int	t_opts;

typedef struct			s_sig_msg
{
	pid_t				sig;
	const char			*msg;
}						t_sig_msg;

typedef struct			s_hist
{
	char				*s;
	int					nb;
	struct s_hist		*next;
	struct s_hist		*prev;
}						t_hist;

typedef struct			s_hash
{
	size_t				hit;
	char				*command;
	char				path[1024];
	struct s_hash		*next;
}						t_hash;

typedef struct			s_edit
{
	t_bool				edited;
	size_t				curr;
	size_t				pos;
	size_t				width;
	size_t				tall;
	size_t				select_pos;
	size_t				max_char;
	int					pos_z;
	int					pos_y;
	int					hist_size;
	short				select;
	char				*tmp;
	char				*incr_search;
	unsigned short		mode;
	unsigned long		kval[NUMBER_OF_KEYS];
	void				(*ft_tab[NUMBER_OF_KEYS])(struct s_edit *e);
	void				(*print_modes[NUMBER_OF_PRINT_MODES])(struct s_edit *e);
	t_hist				*hist;
	t_hist				*head;
}						t_edit;

typedef struct			s_eval
{
	char				*s;
	char				*eval;
	enum e_error		err;
	char				c;
	int					curr;
	int					correc;
}						t_eval;

typedef struct			s_word
{
	enum e_wtype		type;
	char				*word;
	t_bool				paste;
	struct s_word		*next;
}						t_word;

typedef struct			s_redirect
{
	enum e_rtype		t;
	char				*path;
	t_word				*eof;
	int					from;
	int					to;
	char				*heredoc;
	struct s_redirect	*next;
}						t_redirect;

typedef struct			s_tree
{
	t_word				*cmd;
	t_redirect			*r;
	t_envv				*ass;
	int					ret;
	enum e_otype		o_type;
	struct s_tree		*next;
}						t_tree;

typedef struct			s_process
{
	t_envv				*saved_env;
	char				**env;
	int					fd[3];
	int					valid;
	t_bool				builtins;
	t_bool				background;
	int					sig;
	char				*cmd;
	enum e_pstatus		status;
	char				**argv;
	pid_t				pid;
	pid_t				pgid;
	int					ret;
	int					pipe[2];
	struct s_process	*grp;
	struct s_process	*next;
}						t_process;

typedef struct			s_jobs
{
	t_process			*p;
	int					id;
	struct s_jobs		*next;
}						t_jobs;

typedef struct			s_shell
{
	pid_t				pid;
	int					alias_cont;
	int					err;
	pid_t				pgid;
	int					std[3];
	t_bool				interactive;
	t_bool				fc;
	char				*txt;
	char				*builtins[17];
	char				*ptr[100];
	int					loop;
	int					fd;
	int					heredoc;
	t_envv				*env;
	t_envv				*alias;
	t_hist				*hist;
	t_process			*process;
	t_jobs				*jobs;
	t_edit				e;
	char				*clipboard;
	t_hash				**htable;
	struct termios		term;
	struct termios		saved_term;
}						t_shell;

typedef struct			s_fc
{
	char				**av;
	t_hist				*hist;
	t_shell				*shell;
	int					first;
	int					last;
	char				*first_;
	char				*last_;
	t_hist				*hist_first;
	t_hist				*hist_last;
	char				flags[6];
	int					hist_size;
}						t_fc;

#endif
