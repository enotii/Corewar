# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: caking <caking@student.21-school.ru>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/04/12 15:29:32 by caking            #+#    #+#              #
#    Updated: 2020/04/16 22:53:57 by caking           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = asm

LIB = -I libft/libft.h -L./libft -lft

SRC = *.c

OBJ = $(SRC:.c=.o)

HEADER = -I asm.h

FLAGS = -Wall -Wextra -Werror

all: $(NAME)

$(NAME):  $(OBJ)
	make -C libft/
	gcc $(FLAGS) $(OBJ) -o $(NAME) $(LIB)

clean:
	rm -rf libft/*.o
	rm -rf *.o

fclean: clean
	rm -rf $(NAME)
	rm -rf libft/libft.a

re: fclean all

norm:
	norminette -R CheckForbiddenSourceHeader *

debug: 
	gcc -ggdb *.c -I asm.h $(LIB)