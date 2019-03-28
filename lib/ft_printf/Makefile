#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: stdenis <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/11/07 10:22:20 by stdenis           #+#    #+#              #
#    Updated: 2018/11/16 12:33:27 by stdenis          ###   ########.fr        #
#                                                                              #
#******************************************************************************#

include include.mk

NAME	:=	$(LIBFT_PRTF)

SRC=	arguments.c		\
		buffer.c		\
		ft_printf.c		\
		string.c		\
		char.c			\
		integer.c		\
		unsigned.c		\
		pointers.c		\
		hexadecimal.c	\
		print_double.c	\
		double.c		\
		binary.c		\
		unicode.c		\
		utils_unicode.c	\
		transform_ldbl.c\
		utils_double.c	\
		octal.c			\
		ft_putnbrs.c	\
		utils.c			\

SRCDIR	:=	src
INCDIR	:=	inc

BUILDDIR	:=	build
OBJDIR		:=	$(BUILDDIR)/obj

# File used as a command output buffer
TMP		:=	build/tmp.txt

#### COMPILER ####
CC		?=	cc

INCFLAG	:= -I $(INCDIR)
STDFLAG	?=	-std=gnu11
WFLAGS	?=	-Wall -Wextra -Werror -pedantic
CFLAGS	=	$(WFLAGS) $(INCFLAG) $(STDFLAG)

LD		:=	ar
LDFLAG	:=	rcs

SRCLOCA	:=	$(shell find $(SRCDIR) -type d)
OBJLOCA	:=	$(subst $(SRCDIR), $(OBJDIR), $(SRCLOCA))

OBJ		:=	$(addprefix $(OBJDIR)/, $(SRC:.c=.o))
SRC		:=	$(addprefix $(SRCDIR)/, $(SRC))

#### COLORS ####
ifdef TERM
# Ansi excape color sequences
RED			:=	"\033[1;31m"
GREEN		:=	"\033[0;32m"
BGREEN		:=	"\033[1;32m"
BLUE		:=	"\033[0;34m"
YELLOW		:=	"\033[0;33m"
PURPLE		:=	"\033[0;35m"
CYAN		:=	"\033[0;36m"
GREY		:=	"\033[0;37m"

# When printed reset the color
COLRESET	:=	"\033[0m"

# Move the cursor at the begining of the line
MOVELINE	:=	"\033[1A"
# Erase current line
CLEARLINE	:=	"\033[K"

COLOR		= \033[01;34m
NO_COLOR	= \033[00m
OP_COLOR	= \033[1;31m
DONE 		= $(NO_COLOR)[\033[1;32mOK$(NO_COLOR)]

COMPCOLOR	:=	$(GREEN)
LINKCOLOR	:=	$(PURPLE)
ONGOINGCOL	:=	$(YELLOW)
KOCOLOR		:=	$(RED)
RMCOLOR		:=	$(GREY)
DEBUGCOLOR	:=	$(YELLOW)
endif

#############################
#           RULES           #
#############################
#### COMPILE ####
# Standard rule used when just calling $> make
all:		$(NAME)

# Program linkage
$(NAME):	$(OBJ)
	@ $(LD) $(LDFLAG) $(NAME) $(OBJ)
		@printf "\n$(DONE)$(OP_COLOR)$(NAME)$(NO_COLOR)  \n"

# Compilation and .d generation
$(OBJDIR)/%.o:	$(SRCDIR)/%.c | $(OBJDIR)
	@ $(CC) -c $< $(CFLAGS) -o  $@
		@printf "ft_printf$(NO_COLOR)	$(DONE)	$(COLOR)$<$(NO_COLOR)                               \r"

# Dir created to store build cache
$(OBJDIR):
	@ mkdir -p $(OBJLOCA)
$(BUILDDIR):
	@ mkdir -p $(BUILDDIR)

#### LOCAL (Don't recompile lib) ####
lclean:
	@ rm -r $(BUILDDIR) 1> /dev/null 2> /dev/null \
		&& echo $(RMCOLOR)[CLR]$(COLRESET)"	:" obj \
		; (exit 0)

lfclean: lclean
	@ rm -Rf *.dSYM 1> /dev/null 2> /dev/null
	@ rm $(NAME) 1> /dev/null 2> /dev/null \
		&& echo $(RMCOLOR)[CLR]$(COLRESET)"	:" $(NAME) \
		; (exit 0)

lre: lfclean all

#### MANDATORY ####
clean: lclean
	@ rm -f $(TMP)

fclean:	lfclean

re:		fclean all

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


#############################
#          SETTING          #
#############################
# Add rule to phony if they are not based on actual files.
.PHONY: all clean fclean re