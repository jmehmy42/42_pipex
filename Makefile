# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jmehmy <jmehmy@student.42lisboa.com>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/06 16:59:07 by jmehmy            #+#    #+#              #
#    Updated: 2025/03/06 16:59:07 by jmehmy           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex
CC = cc
FLAGS = -Wall -Werror -Wextra

SRC_FILES = pipex.c find_path.c utils.c
OBJ_DIR = obj
OBJS = $(patsubst %.c, $(OBJ_DIR)/%.o, $(SRC_FILES))

LIBFT = includes/libft/libft.a

all: $(NAME) 

$(NAME): $(OBJS) $(LIBFT)
	@$(CC) $(FLAGS) $(OBJS) $(LIBFT) -g -o $(NAME)
	@echo "\n\033[1m\033[32mPipex Compiled Successfully! ᕦ(\033[31m♥\033[32m_\033[31m♥\033[32m)ᕤ\033[1m\\n"

$(OBJ_DIR)/%.o: %.c | $(OBJ_DIR)
	@$(CC) $(FLAGS) -c -g $< -o $@

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

$(LIBFT):
	@$(MAKE) -C includes/libft -s
	
clean:
	@rm -rf $(OBJ_DIR)
	@make clean -C includes/libft -s

fclean: clean
	@rm -f $(NAME)
	@make fclean -C includes/libft -s
	@echo "\n\033[1m\\033[31mDeleting EVERYTHING! ⌐(ಠ۾ಠ)¬\033[1m\\n"

re: fclean all

.PHONY: all fclean clean re

