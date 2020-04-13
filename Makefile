# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ilya <ilya@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/04/12 15:29:32 by caking            #+#    #+#              #
#    Updated: 2020/04/13 17:13:48 by ilya             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = asm

LIB = -I libft/libft.h -L./libft -lft

SRC = asm_main.c

OBJ = $(SRC:.c=.o)

HEADER = -I asm.h

all: $(NAME)

$(NAME):  $(OBJ)
	make -C libft/
	gcc -Wall -Wextra -Werror $(OBJ) -o $(NAME) $(LIB)

clean:
	rm -rf libft/*.o
	rm -rf *.o

fclean: clean
	rm -rf $(NAME)
	rm -rf libft/libft.a

re: fclean all

norm:
	norminette -R CheckForbiddenSourceHeader *
