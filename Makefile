# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ptruffau <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/11/16 11:16:13 by ptruffau          #+#    #+#              #
#    Updated: 2019/03/26 17:18:28 by stdenis          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=		42sh
GIT 		=		https://github.com/ptruffault/42sh.git

SRC		=	\
	main.c				\
	signal.c			\
	init_shell.c		\
	ft_get_set.c 		\
	ft_free_tshell.c	\
	init_envv.c			\
	init_intern.c		\
	\
	exec/ft_execve.c			\
	exec/exec.c					\
	exec/exec_pipe.c			\
	exec/exec_file.c			\
	exec/redirection.c			\
	exec/redirect_builtins.c	\
	exec/bin_search.c			\
	exec/init_process.c			\
	\
	eval/eval_tools.c		\
	eval/tree_tools.c		\
	eval/lexer_tools.c		\
	eval/lexer.c			\
	eval/free_tools.c		\
	eval/get_instruction.c	\
	eval/heredoc_content.c	\
	eval/token.c			\
	eval/redirect.c			\
	eval/alias.c			\
	eval/t_word_tools.c		\
	\
	builtins/ft_echo.c					\
	builtins/ft_jobs.c					\
	builtins/fg_bg.c					\
	builtins/ft_cd.c					\
	builtins/ft_cdpath.c				\
	builtins/run_builtin.c				\
	builtins/ft_export.c				\
	builtins/ft_type.c					\
	builtins/ft_exit.c					\
	builtins/type_tools.c				\
	builtins/ft_alias.c					\
	builtins/hi.c						\
	builtins/check_builtins.c			\
	\
	builtins/ft_fc/ft_fc.c						\
	builtins/ft_fc/ft_fc_search_hist_parser.c	\
	builtins/ft_fc/ft_fc_search_hist.c			\
	builtins/ft_fc/ft_fc_option_e.c				\
	builtins/ft_fc/ft_fc_option_l.c				\
	builtins/ft_fc/ft_fc_option_s.c				\
	\
	get_input/curs_move.c		\
	get_input/get_input.c		\
	get_input/handle_input.c	\
	get_input/history.c			\
	get_input/input_tools.c		\
	get_input/print_line.c		\
	get_input/setup.c			\
	get_input/get_history.c		\
	get_input/ft_cop_pas.c		\
	get_input/ft_jump_word.c	\
	get_input/arrow_move.c		\
	get_input/ft_select.c		\
	get_input/clear_and_all.c	\
	get_input/use_termcaps.c	\
	get_input/term_settings.c	\
	get_input/ft_jump_line.c	\
	\
	expansion/exp.c				\
	expansion/exp_parenth.c		\
	expansion/cut_string.c		\
	expansion/parenth_tools.c	\
	\
	process/kill_process.c		\
	process/ft_wait.c			\
	process/process_tools.c		\
	\
	tenvv/ft_get_set_envv.c		\
	tenvv/tenvv_tools.c			\
	tenvv/tenvv_tools_2.c		\
	tenvv/tenvv_to_tab.c		\
	tenvv/ft_setenv.c			\
	tenvv/ft_unsetenv.c

#### COMPILER ####
CC		?=	cc

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

INCFLAG		:=	-I $(INCDIR) $(LIB_INC)
STDFLAG		?=	-std=gnu11
WFLAGS		?=	-Wall -Wextra -Werror -pedantic -g
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

$(NAME):	$(OBJ)| $(LIBFT_PATH)/$(LIBFT) $(LIBFT_PRTF_PATH)/$(LIBFT_PRTF)
	@echo "$(OP_COLOR) building $(NAME)$(NO_COLOR)"
	@$(LD) -o $(NAME) $(OBJ) $(LDFLAG)
	@printf "$(DONE)$(OP_COLOR)$(NAME)$(NO_COLOR)  \n"


$(OBJDIR)/%.o:	$(SRCDIR)/%.c | $(OBJDIR) $(DEPDIR)
	@touch $<
	@$(CC) -c $< $(CFLAGS) -o  $@ && printf "$(DONE)	:  $(COLOR)$<$(NO_COLOR)\n" \
			|| printf "$(KO)	<-  $(COLOR)$<$(NO_COLOR)\n"
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
	@valgrind --leak-check=full --show-leak-kinds=all -v ./$(NAME)

save: fclean clear
	@echo > sys/.42history
	@git add -A && git commit -m "make save" && git push \
	&& printf "$(COLOR)save$(NO_COLOR) : $(DONE)\n" || printf"$(OP_COLOR)save : KO\n$(NO_COLOR)"


#############################
#          SETTING          #
#############################
# Add rule to phony if they are not based on actual files.
.PHONY: all re
.PHONY: debug rdebug debugclean
.PHONY: warn
.PHONY: lclean lfclean lre val exe fre
.PHONY: clear sclean clean fclean save

#############################
#         DEPENDENCY        #
#############################
# Include all custom dependency rules created in .d's
# the '-' prevent error in case of non existing files
-include $(DEP)