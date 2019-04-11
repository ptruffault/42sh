# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fstadelw <fstadelw@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/12/18 00:55:10 by fstadelw          #+#    #+#              #
#    Updated: 2018/12/18 03:54:20 by fstadelw         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC	=	$(wildcard *.c)
PRG	=	$(basename $(SRC))

all: $(PRG)

%: %.c
	$(CC) $< -o $@

clean:
	rm $(PRG)

exec:
	@ for file in `echo $(PRG) | tr ' ' '\n' | sort -g` ; do \
		/bin/echo -n [$$file]' :	' ; \
		echo "./$$file" | tcsh ; \
		echo ; \
	done

test:
	@ for file in `echo $(PRG) | tr ' ' '\n' | sort -g` ; do \
		/bin/echo -n [$$file]' :	' ; \
		echo "./$$file" | ../../minishell ; \
		echo ; \
	done
