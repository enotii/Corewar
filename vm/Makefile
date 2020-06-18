# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sscottie <sscottie@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/03/14 14:32:21 by sscottie          #+#    #+#              #
#    Updated: 2020/06/19 00:36:23 by sscottie         ###   ########.fr        #
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
				game.c

SOURCES = $(addprefix $(SOURCES_PATH), $(SOURCES_NAME))
OBJECTS_NAME = $(SOURCES_NAME:%.c=%.o)
OBJECTS = $(addprefix $(OBJECTS_PATH), $(OBJECTS_NAME))
OBJ = $(addprefix $(OBJDIR), $(SRC:.c=.o))

all : $(NAME) 

$(NAME): $(PRINTF) $(OBJECTS) 
	$(CC) $(CFLAGS) $(INCLUDES) $(PRINTF) -o $@ $(OBJECTS)

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

#.PHONY: all clean fclean re
#
## COLORS
#
#GREEN = \033[0;32m
#RED = \033[0;31m
#RED_B = \033[1;31m
#BLUE = \033[1;34m
#RESET = \033[0m
#
#NAME 		= corewar
#CFLAGS		= -Wall -Wextra -Werror
#INC			= -I include
#FT_PF 		= ./lib/ft_printf/
#SRC_DIR		= ./src/
#OBJ_DIR 	= ./temp/
#PF_A		= ./lib/ft_printf/libftprintf.a
#HEADER		= vm.h
#PF_H		= ft_printf.h
#PF_INC		= -I ./lib/ft_printf/include
#
#SRC_VM_C	= corewar.c \
#				player.c \
#				parcer.c
#
#SRC_VM	= $(addprefix $(SRC_DIR), $(SRC_VM_C))
#OBJ_VM	= $(addprefix $(OBJ_DIR), $(patsubst %.c, %.o, $(SRC_VM_C)))
#
#all: $(NAME) 
#
#$(NAME):: pf
#$(NAME):: $(SRC_VM) $(OBJ_DIR) $(OBJ_VM) 
#	@echo "$(BLUE)corewar:   $(GREEN)Compiling$(RESET)"
#	@gcc $(CFLAGS) $(OBJ_VM) -o $(NAME) $(INC) $(PF_INC) $(PF_A)
#	@echo "$(BLUE)corewar:   $(GREEN)corewar has been created$(RESET)"
#
#
#$(OBJ_DIR): 
#	@mkdir -p $(OBJ_DIR)
#	@gcc $(CFLAGS) -c $(SRC_VM) -o $(OBJ_VM) $(INC) $(PF_INC)
#
## $(OBJ_DIR)%.o: %.c $(HEADER)
## 	gcc $(CFLAGS) -c $(SRC_LS) -o $(OBJ_LS) $(INC) $(PF_INC)
#
#pf: 
#	@echo "$(BLUE)ft_printf: $(GREEN)Compiling $(RESET)"	
#	@make -C ./lib/ft_printf/
#
#clean:
#	@make -C ./lib/ft_printf clean
#	@echo "$(RED_B)corewar:   $(RED)object files have been deleted$(RESET)"
#	@rm -rf $(OBJ_DIR)
#
#fclean:
#	@rm -rf $(OBJ_DIR)
#	@rm -rf $(NAME)
#	@make -C ./lib/ft_printf fclean
#	@echo "$(RED_B)corewar:  $(RED) corewar have been deleted$(RESET)" 
#
#re: fclean all