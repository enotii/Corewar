# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sscottie <sscottie@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/03/14 14:32:21 by sscottie          #+#    #+#              #
#    Updated: 2020/06/24 11:43:02 by sscottie         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.PHONY: all, clean, fclean, re, obj, asm

NAME = corewar
CC = gcc
FLAGS = -Wall -Werror -Wextra -g
SOURCES_PATH = ./src/
OBJECTS_PATH = ./temp/
PRINTF_DIR = ./lib/ft_printf
PRINTF = $(PRINTF_DIR)/libftprintf.a
INCLUDE = include/vm.h include/op.h lib/ft_printf/include/ft_printf.h \
			lib/ft_printf/include/libft.h lib/ft_printf/include/get_next_line.h
INCLUDES = -I ./include -I ./lib/ft_printf/include

SOURCES_NAME = corewar.c \
				parcer.c \
				player.c \
				map.c \
				ft_add.c \
				ft_aff.c \
				ft_and.c \
				ft_fork_lfork.c \
				ft_ld.c \
				ft_ldi.c \
				ft_liba.c \
				ft_live.c \
				ft_or_xor.c \
				ft_st.c \
				ft_sti.c \
				ft_sub.c \
				ft_zjmp.c \
				do_cmd.c \
				carriage_list.c \
				code_print.c \
				reader.c \
				arguments.c \
				game.c \
				viz_algo.c \
				viz_init.c \
				write_map.c

SOURCES = $(addprefix $(SOURCES_PATH), $(SOURCES_NAME))
OBJECTS_NAME = $(SOURCES_NAME:%.c=%.o)
OBJECTS = $(addprefix $(OBJECTS_PATH), $(OBJECTS_NAME))
OBJ = $(addprefix $(OBJDIR), $(SRC:.c=.o))

all : $(NAME) 

$(NAME): $(PRINTF) $(OBJECTS) 
	$(CC) $(CFLAGS) $(INCLUDES) -lncurses $(PRINTF) -o $@ $(OBJECTS)

$(PRINTF): FORCE
	make -C $(PRINTF_DIR)

FORCE:

$(OBJECTS_PATH)%.o: $(SOURCES_PATH)%.c $(INCLUDE)
	@mkdir $(OBJECTS_PATH) 2>/dev/null || echo "" > /dev/null
	$(CC) $(FLAGS) $(INCLUDES) -c $< -o $@


clean :
		@/bin/rm -f $(OBJECTS)
	    @/bin/rm -rf $(OBJECTS_PATH)
	    @/bin/rm -f *.h.gch
	    @/bin/rm -f .*.swp
		@make clean -C $(PRINTF_DIR)

fclean : clean
		@make fclean -C $(PRINTF_DIR)
		@/bin/rm -f $(NAME)

re : fclean all
