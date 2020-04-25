# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: caking <caking@student.21-school.ru>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/04/12 15:29:32 by caking            #+#    #+#              #
#    Updated: 2020/04/25 16:56:32 by caking           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = asm

LIB = -I libft/ -L./libft -lft

SRC = asm_main.c tokens.c

OBJ = $(SRC:.c=.o)

HEADER = -I asm.h

FLAGS = -Wall -Wextra -Werror

all: $(NAME)

$(NAME): $(OBJ)
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
	gcc -ggdb $(SRC) $(LIB)

byte:
	xxd 42.cor > 1.hex
byte2:
	xxd 42 > 2.hex
change: 
	diff 1.hex 2.hex
