# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: caking <caking@student.21-school.ru>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/04/12 15:29:32 by caking            #+#    #+#              #
#    Updated: 2020/06/25 20:24:23 by caking           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME1 = asm

NAME2 = dasm

NAME3 = corewar

LIB = -I libft/ -L./libft -lft

SRC1 = assembler/asm_main.c assembler/tokens.c assembler/tokens_func.c\
 assembler/tokens_func2.c assembler/parse_tokens.c assembler/parse_to_byte.c\
  assembler/parse_to_byte2.c assembler/transform_func.c assembler/handle_func.c\
   assembler/parse_to_byte3.c assembler/parse_tokens2.c

SRC2 = disass/main.c disass/disass_func.c disass/disass_func2.c

OBJ1 = $(SRC1:.c=.o)

OBJ2 = $(SRC2:.c=.o)

FLAGS = -Wall -Wextra -Werror -ggdb

all: $(NAME1) $(NAME2) $(NAME3)

$(NAME1): $(OBJ1)
	make -C libft/
	gcc $(FLAGS) $(OBJ1) -o $(NAME1) $(LIB)

$(NAME2): $(OBJ2)
	gcc $(FLAGS) $(OBJ2) -o $(NAME2) $(LIB)

$(NAME3):
	make -C vm/
	mv ./vm/corewar ./corewar

clean:
	rm -rf libft/*.o
	rm -rf assembler/*.o
	rm -rf disass/*.o
	make -C vm/ clean

fclean: clean
	rm -rf $(NAME1) $(NAME2) $(NAME3)
	rm -rf libft/libft.a
	make -C vm/ fclean

re: fclean all