# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fstadelw <fstadelw@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/12/18 00:55:10 by fstadelw          #+#    #+#              #
#    Updated: 2019/01/01 03:05:31 by fstadelw         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

all:
	@ ./test.sh

trace:
	@ VALGRIND='true' ./test.sh

clean:
	@ $(MAKE) -C sig clean > /dev/null 2> /dev/null; exit 0

.PHONY: all trace clean
