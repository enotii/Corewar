# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: caking <caking@student.21-school.ru>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/04/12 15:29:32 by caking            #+#    #+#              #
#    Updated: 2020/06/15 22:04:06 by caking           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME1 = asm

NAME2 = dasm

LIB = -I libft/ -L./libft -lft

SRC1 = assembler/asm_main.c assembler/tokens.c

SRC2 = disass/main.c

OBJ1 = $(SRC1:.c=.o)

OBJ2 = $(SRC2:.c=.o)

FLAGS = -Wall -Wextra -Werror

all: $(NAME1) $(NAME2)

$(NAME1): $(OBJ1)
	make -C libft/
	gcc $(FLAGS) $(OBJ1) -o $(NAME1) $(LIB)

$(NAME2): $(OBJ2)
	make -C libft/
	gcc $(FLAGS) $(OBJ2) -o $(NAME2) $(LIB)

clean:
	rm -rf libft/*.o
	rm -rf assembler/*.o
	rm -rf disass/*.o

fclean: clean
	rm -rf $(NAME1) $(NAME2)
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
	diff 1.hex 2.hex > change.diff
