# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ptruffau <ptruffau@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/11/16 11:16:13 by ptruffau          #+#    #+#              #
#    Updated: 2019/04/27 12:00:31 by fstadelw         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= 42sh

UNAME	:= $(shell uname)

ifeq ($(UNAME), Linux)
SIG		:= signal_unix.c
endif

ifeq ($(UNAME), Darwin)
SIG		:=	signal.c \
			signal_handle.c
endif

SRC		:=	\
	main.c				\
	$(SIG)              \
	ft_get_set.c 		\
	\
	setup_exit/free_tools_shell.c \
	setup_exit/init_envv.c		\
	setup_exit/init_intern.c	\
	setup_exit/init_shell.c		\
	setup_exit/free_tools.c		\
	\
	exec/ft_execve.c			\
	exec/exec_tools.c 			\
	exec/exec.c					\
	exec/pipe_tools.c			\
	exec/exec_pipe.c			\
	exec/exec_file.c			\
	exec/redirection.c			\
	exec/redirect_builtins.c	\
	exec/bin_search.c			\
	\
	eval/eval_tools.c		\
	eval/tree_tools.c		\
	eval/lexer_tools.c		\
	eval/lexer.c			\
	eval/get_instruction.c	\
	eval/redirect_tools.c  \
	eval/heredoc_content.c	\
	eval/token.c			\
	eval/redirect.c			\
	eval/alias.c			\
	eval/t_word_tools.c		\
	\
	builtins/ft_echo.c					\
	builtins/ft_cd.c					\
	builtins/ft_cdpath.c				\
	builtins/run_builtin.c				\
	builtins/ft_export.c				\
	builtins/ft_exit.c					\
	builtins/print_utility.c			\
	builtins/ft_alias.c					\
	builtins/check_builtins.c			\
	\
	builtins/ft_hash/ft_hash.c		\
	builtins/ft_hash/hash_utility.c	\
	\
	builtins/ft_test/ft_test.c		\
	builtins/ft_test/test_utility.c	\
	\
	builtins/type/ft_type.c					\
	builtins/type/type_tools.c				\
	\
	builtins/ft_fc/ft_fc.c						\
	builtins/ft_fc/ft_fc_search_hist_parser.c	\
	builtins/ft_fc/ft_fc_search_hist.c			\
	builtins/ft_fc/ft_fc_option_e.c				\
	builtins/ft_fc/ft_fc_option_l.c				\
	builtins/ft_fc/ft_fc_option_s.c				\
	builtins/ft_fc/flags_lexer.c				\
	builtins/ft_fc/fc_free_editor.c				\
	\
	builtins/jobs/fg_bg.c \
	builtins/jobs/ft_jobs.c \
	builtins/jobs/jobs_prompt.c \
	builtins/jobs/hi.c \
	\
	get_input/cursor/curs_move.c		\
	get_input/cursor/ft_cop_pas.c		\
	get_input/cursor/ft_jump_word.c		\
	get_input/cursor/arrow_move.c		\
	get_input/cursor/ft_select.c		\
	get_input/cursor/clear_and_all.c	\
	get_input/cursor/ft_jump_line.c		\
	\
	get_input/history/history.c			\
	get_input/history/hist_expanse.c	\
	get_input/history/seek_n_replace.c	\
	get_input/history/ft_incr_search.c	\
	\
	get_input/get_input.c		\
	get_input/valid_line.c		\
	get_input/handle_input.c	\
	get_input/input_tools.c		\
	get_input/print_line.c		\
	get_input/setup.c			\
	get_input/use_termcaps.c	\
	get_input/term_settings.c	\
	get_input/ft_tab.c			\
	get_input/prompt.c			\
	get_input/gi_init_tab.c		\
	get_input/valid_tools.c		\
	\
	autocompletion/check_line.c			\
	autocompletion/utility_handler.c	\
	autocompletion/tabl_handler.c		\
	autocompletion/binary_completion.c	\
	autocompletion/files_completion.c	\
	autocompletion/environ_completion.c	\
	\
	expansion/exp.c				\
	expansion/expansion_tools.c	\
	expansion/exp_tools.c 		\
	expansion/exp_parenth.c		\
	expansion/cut_string.c		\
	expansion/cut_glob.c		\
	expansion/parenth_tools.c	\
	\
	process/ft_kill.c			\
	process/wait_process.c		\
	process/jobs_tools.c		\
	process/init_process.c		\
	process/init_pipe.c			\
	process/job_search.c 		\
	\
	tenvv/tenvv_tools.c			\
	tenvv/tenvv_tools_tmp.c		\
	tenvv/tenvv_to_tab.c		\
	tenvv/ft_setenv.c			\
	tenvv/ft_unsetenv.c			\
	\
	history/deload_history.c	\
	history/get_history.c		\

SRCDIR	:=	srcs
INCDIR	:=	includes
LIBDIR	:=	lib
TESTDIR	:=	test

BUILDDIR	:=	bin
OBJDIR		:=	$(BUILDDIR)/obj
DBGDIR		:=	$(BUILDDIR)/debug
DEPDIR		:=	$(BUILDDIR)/dep

#### LIBRARY ####
# Printf
LIBFT_PRTF		:=	libftprintf.a
LIBFT_PRTF_PATH :=  $(LIBDIR)/ft_printf
LIB_LINK		:= -L $(LIBFT_PRTF_PATH) -l ftprintf
LIB_INC			:= -I $(LIBFT_PRTF_PATH)/inc

# Libft
LIBFT		:=	libft.a
LIBFT_PATH	:= $(LIBDIR)/libft
LIB_LINK	+= -L $(LIBFT_PATH) -l ft
LIB_INC		+= -I $(LIBFT_PATH)/includes

#### COMPILER ####
CC			?=	cc

INCFLAG		:=	-I $(INCDIR) $(LIB_INC)
ifeq ($(UNAME), Linux)
STDFLAG		?=	-std=gnu11
endif

ifeq ($(UNAME), Darwin)
STDFLAG		?=	-ansi
endif
WFLAGS		?=	-Wall -Wextra -Werror -pedantic
CFLAGS		=	$(WFLAGS) $(INCFLAG) $(STDFLAG)

DEPGEN		:=	$(CC)
DEPFLAG		:=	-MM $(INCFLAG)

LD			:=	$(CC)
LDFLAG		=	$(LIB_LINK) -ltermcap
LDFLAG		+=	-Wno-unused-command-line-argument $(WFLAGS)

#############################
#    MAKEFILE VARIABLES     #
#############################
#### FILE STRUCTURE ####
# *LOCA is the list of all subdirectory in a directory
SRCLOCA	:=	$(shell find $(SRCDIR) -type d)
OBJLOCA	:=	$(subst $(SRCDIR), $(OBJDIR), $(SRCLOCA))
DBGLOCA	:=	$(subst $(SRCDIR), $(DBGDIR), $(SRCLOCA))
DEPLOCA	:=	$(subst $(SRCDIR), $(DEPDIR), $(SRCLOCA))

OBJ		:=	$(addprefix $(OBJDIR)/, $(SRC:.c=.o))
DBG		:=	$(addprefix $(DBGDIR)/, $(SRC:.c=.o))
DEP		:=	$(addprefix $(DEPDIR)/, $(SRC:.c=.d))
SRC		:=	$(addprefix $(SRCDIR)/, $(SRC))

COLOR		= 		\033[01;34m
NO_COLOR	= 		\033[00m
OP_COLOR	= 		\033[1;31m
DONE 		= 		$(NO_COLOR)[\033[1;32mOK$(NO_COLOR)]
KO			= 		$(NO_COLOR)[\033[00;31mKO$(NO_COLOR)]


#############################
#           RULES           #
#############################
#### COMPILE ####
all: $(NAME)

$(NAME):	$(OBJ) $(LIBFT_PATH)/$(LIBFT) $(LIBFT_PRTF_PATH)/$(LIBFT_PRTF)
	@ echo "$(OP_COLOR) building $(NAME)$(NO_COLOR)"
	@ $(LD) -o $(NAME) $(OBJ) $(LDFLAG)
	@ printf "$(DONE)$(OP_COLOR)$(NAME)$(NO_COLOR)\n"


$(OBJDIR)/%.o:	$(SRCDIR)/%.c | $(OBJDIR) $(DEPDIR)
	@ $(CC) -c $< $(CFLAGS) -o $@ \
		&& printf "$(DONE)	: $(COLOR)$<$(NO_COLOR)\n" \
		|| (printf "$(KO)	<-  $(COLOR)$<$(NO_COLOR)\n" ; false)
	@ $(DEPGEN) -c $< $(DEPFLAG) -MQ $@ \
			> $(subst $(SRCDIR), $(DEPDIR), $(<:.c=.d))

$(LIBFT_PATH)/$(LIBFT):
	@ $(MAKE) -C $(LIBFT_PATH) --no-print-directory

$(LIBFT_PRTF_PATH)/$(LIBFT_PRTF):
	@ $(MAKE) -C $(LIBFT_PRTF_PATH) --no-print-directory

# Dir created to store build cache
$(OBJDIR):
	@ mkdir -p $(OBJLOCA)
$(DBGDIR):
	@ mkdir -p $(DBGLOCA)
$(DEPDIR):
	@ mkdir -p $(DEPLOCA)
$(BUILDDIR):
	@ mkdir -p $(BUILDDIR)


# Recompile with as much warning as possible
warn:	WFLAGS := -Wall -Wextra -ansi -Wpedantic -Wno-vla
warn:	WFLAGS += -Wstrict-prototypes -Wunreachable-code  -Wwrite-strings
warn:	WFLAGS += -Wpointer-arith -Wbad-function-cast -Wcast-align -Wcast-qual
CLANG_INSTALLED	:= $(shell which clang > /dev/null 2> /dev/null && echo yes)
# If clang is installed also add this exclusive warning
ifdef CLANG_INSTALLED
warn:	CC := clang
warn:	WFLAGS += -Weverything -Wno-padded -Wno-missing-noreturn
endif
warn:	lre

#### DEBUGING ####
$(DBGDIR)/%.o:		$(SRCDIR)/%.c | $(DBGDIR) $(DEPDIR)
	@printf "$(COLOR)$<$(NO_COLOR) -> "
	@touch $<
	@ $(CC) -c $< $(CFLAGS) -o  $@ && printf "$(DONE)\n" || printf "$(KO)\n"
	@ $(DEPGEN) -c $< $(DEPFLAG) -MQ $@ \
		> $(subst $(SRCDIR), $(DEPDIR), $(<:.c=.d))

debug:	WFLAGS		:= -g
debug:	$(DBG) | $(LIBFT_PATH)/$(LIBFT) $(LIBFT_PRTF_PATH)/$(LIBFT_PRTF)
	@echo "$(OP_COLOR) building $(NAME)$(NO_COLOR)"
	@$ $(LD) -o $(NAME) $(DBG) $(LDFLAG)
	@printf "$(DONE)$(OP_COLOR)$(NAME)$(NO_COLOR)  \n"

debugclean:
	@ rm -r $(DBGDIR) 1> /dev/null 2> /dev/null \
		&& printf "$(OP_COLOR)[CLR]$(NO_COLOR)"	:" debug obj" \
		; (exit 0)

rdebug: debugclean debug

clear:
	@clear

sclean:
	@rm -rf $(OBJ) $(NAME)

#### LOCAL (Don't recompile lib) ####
lclean:
	@ rm -r $(BUILDDIR) 1> /dev/null 2> /dev/null \
		&& printf "$(OP_COLOR)[CLR]$(NO_COLOR)	: obj\n" \
		; (exit 0)

lfclean: lclean
	@ rm -Rf *.dSYM 1> /dev/null 2> /dev/null
	@ rm $(NAME) 1> /dev/null 2> /dev/null \
		&& printf "$(OP_COLOR)[CLR]$(NO_COLOR)	: $(NAME)\n" \
		; (exit 0)

lre: lfclean all

#### MANDATORY ####
clean: lclean
	@ $(MAKE) -C $(LIBFT_PATH) --no-print-directory clean
	@ $(MAKE) -C $(TESTDIR) --no-print-directory clean
	@ $(MAKE) -C $(LIBFT_PRTF_PATH) --no-print-directory clean

fclean:	lfclean
	@ $(MAKE) -C $(LIBFT_PATH) --no-print-directory fclean
	@ $(MAKE) -C $(LIBFT_PRTF_PATH) --no-print-directory fclean

re:		fclean all

fre: clear sclean all

exe: all
	./$(NAME)

val: all
	@ valgrind --leak-check=full --show-leak-kinds=all -v ./$(NAME)

save: fclean clear
	@ git add --all && git commit -m "make save" && git push

test:
	@ $(MAKE) -C $(TESTDIR) --no-print-directory fast

full-test:
	@ $(MAKE) -C $(TESTDIR) --no-print-directory

#############################
#          SETTING          #
#############################
# Add rule to phony if they are not based on actual files.
.PHONY: all re
.PHONY: debug rdebug debugclean
.PHONY: warn
.PHONY: lclean lfclean lre val exe fre
.PHONY: clear sclean clean fclean save
.PHONY: full-test test save val exe fre

#############################
#         DEPENDENCY        #
#############################
# Include all custom dependency rules created in .d's
# the '-' prevent error in case of non existing files
-include $(DEP)
