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

NAME		=	libft.a

GIT 		= https://github.com/ptruffault/libft.git

FILES = ft_atoi.c			\
		ft_close.c			\
		ft_error.c			\
		ft_freestrarr.c		\
		ft_isalnum.c		\
		ft_isalpha.c		\
		ft_isascii.c		\
		ft_isdigit.c		\
		ft_isempty.c		\
		ft_isequal.c		\
		ft_ismaj.c			\
		ft_ismin.c			\
		ft_isprint.c		\
		ft_isspace.c		\
		ft_itoa.c			\
		ft_memcpy.c			\
		ft_memset.c			\
		ft_new_path.c		\
		ft_open.c			\
		ft_putchar.c		\
		ft_putchar_fd.c		\
		ft_putendl.c		\
		ft_putendl_fd.c		\
		ft_putnbr.c			\
		ft_putnbr_fd.c		\
		ft_putstr.c			\
		ft_putstr_fd.c		\
		ft_str_startwith.c	\
		ft_stradd_char.c	\
		ft_strappend.c		\
		ft_strcat.c			\
		ft_strchr.c			\
		ft_strchr_end.c		\
		ft_strcmp.c			\
		ft_strcpy.c			\
		ft_strdel.c			\
		ft_strdup.c			\
		ft_strequ.c			\
		ft_strinsert_char.c	\
		ft_strjoin.c		\
		ft_strjoin_add.c	\
		ft_strjoin_fr.c		\
		ft_strlcat.c		\
		ft_strlen.c			\
		ft_strncat.c		\
		ft_strncmp.c		\
		ft_strncpy.c		\
		ft_strndup.c		\
		ft_strnequ.c		\
		ft_strnew.c			\
		ft_strpull.c		\
		ft_strrchr.c		\
		ft_strsplit.c		\
		ft_strstr.c			\
		ft_strsub.c			\
		ft_tolower.c		\
		ft_toupper.c		\
		get_next_line.c		\

#### COMPILER ####
CC		?=	cc

FLAG		 = -Wall -Werror -Wextra -g

FILE_FOLDER	= ./srcs/
OBJ_FOLDER 	= ./bin/

SRC			= $(addprefix $(FILE_FOLDER), $(FILES))
OBJ			= $(addprefix $(OBJ_FOLDER), $(FILES:.c=.o))

COLOR		= \033[01;34m
NO_COLOR	= \033[00m
OP_COLOR	= \033[1;31m
DONE 		= $(NO_COLOR)[\033[1;32mOK$(NO_COLOR)]


all:  Makefile bin srcs auteur $(NAME)

$(NAME): $(OBJ) 
	@ar rc $@ $^
	@ranlib $@
	@printf "\n$(DONE)$(OP_COLOR)$(NAME)$(NO_COLOR)  \n"

auteur:
	@echo "ptruffau" > auteur

bin:
	@mkdir $@

srcs:
	@mkdir $@

bin/%.o: $(FILE_FOLDER)%.c 
	@$(CC) $(FLAG) -I includes -c $< -o $@
	@printf "libft$(NO_COLOR)	$(DONE)	$(COLOR)$<$(NO_COLOR)                               \r"

clean:
	@rm -rf bin/*
	@echo "$(OP_COLOR)Cleaning (libft/*.o)\t $(DONE)"

fclean: clean
	@echo "$(OP_COLOR)Cleaning (libft/libft.a) $(DONE)"
	@rm -rf $(NAME)

re: fclean all

chmod:
	@chmod 777 *
	@chmod 777 srcs/*
	@chmod 777 srcs/tenvv/*
	@chmod 777 includes/*

save: clean fclean
	@git add * $(SRCS)
	@git commit -m "[make save]"
	@git push
	@echo "\t$(DONE)"

update:
	@echo "download lastest $(NAME) version"
	@clear && rm -rf * && git clone $(GIT) tmpfold
	@mv tmpfold/* . && rm -rf tmpfold

.PHONY: all clean fclean re chmod save update


































