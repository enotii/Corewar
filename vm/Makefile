# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sscottie <sscottie@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/03/14 14:32:21 by sscottie          #+#    #+#              #
#    Updated: 2020/03/14 16:31:12 by sscottie         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.PHONY: all clean fclean re

# COLORS

GREEN = \033[0;32m
RED = \033[0;31m
RED_B = \033[1;31m
BLUE = \033[1;34m
RESET = \033[0m

NAME 		= corewar
CFLAGS		= -Wall -Wextra -Werror
INC			= -I include
FT_PF 		= ./lib/ft_printf/
SRC_DIR		= ./src/
OBJ_DIR 	= ./temp/
PF_A		= ./lib/ft_printf/libftprintf.a
HEADER		= vm.h
PF_H		= ft_printf.h
PF_INC		= -I ./lib/ft_printf/include

SRC_VM_C		= corewar.c \

SRC_VM	= $(addprefix $(SRC_DIR), $(SRC_VM_C))
OBJ_VM	= $(addprefix $(OBJ_DIR), $(patsubst %.c, %.o, $(SRC_VM_C)))

all: $(NAME) 

$(NAME):: pf
$(NAME):: $(SRC_VM) $(OBJ_DIR) $(OBJ_VM) 
	@echo "$(BLUE)corewar:   $(GREEN)Compiling$(RESET)"
	@gcc $(CFLAGS) $(OBJ_VM) -o $(NAME) $(INC) $(PF_INC) $(PF_A)
	@echo "$(BLUE)corewar:   $(GREEN)corewar has been created$(RESET)"


$(OBJ_DIR): 
	@mkdir -p $(OBJ_DIR)
	@gcc $(CFLAGS) -c $(SRC_VM) -o $(OBJ_VM) $(INC) $(PF_INC)

# $(OBJ_DIR)%.o: %.c $(HEADER)
# 	gcc $(CFLAGS) -c $(SRC_LS) -o $(OBJ_LS) $(INC) $(PF_INC)

pf: 
	@echo "$(BLUE)ft_printf: $(GREEN)Compiling $(RESET)"	
	@make -C ./lib/ft_printf/

clean:
	@make -C ./lib/ft_printf clean
	@echo "$(RED_B)corewar:   $(RED)object files have been deleted$(RESET)"
	@rm -rf $(OBJ_DIR)

fclean:
	@rm -rf $(OBJ_DIR)
	@rm -rf $(NAME)
	@make -C ./lib/ft_printf fclean
	@echo "$(RED_B)corewar:  $(RED) corewar have been deleted$(RESET)" 

re: fclean all