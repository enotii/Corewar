# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: caking <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/12/07 21:28:35 by caking            #+#    #+#              #
#    Updated: 2018/12/07 21:47:09 by caking           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a
PATH_SRC = ./srcs
SRC = $(PATH_SRC)/*.c
HEADER = ./includes/libft.h
OBJ =  *.o
all: $(NAME)
$(NAME):
	gcc -Wall -Wextra -Werror -c *.c -I libft.h
	ar rc libft.a $(OBJ)
	ranlib libft.a
clean:
	rm -rf *.o
fclean: clean
	rm -rf $(NAME)
re: fclean all


