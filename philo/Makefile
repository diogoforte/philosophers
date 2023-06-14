# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dinunes- <dinunes-@student.42lisboa.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/05 10:54:09 by dinunes-          #+#    #+#              #
#    Updated: 2023/05/05 10:54:09 by dinunes-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#Program name
NAME = philo

# Compiler
CC = cc
CFLAGS = -Werror -Wextra -Wall -pthread #-fsanitize=thread

# Includes
INC = -I ./inc/

# Sources and Objects paths
SRC_PATH = src/
OBJ_PATH = obj/

# Sources
SRC = $(addprefix $(SRC_PATH), checker.c init.c main.c routine.c threads.c utils.c)

# Objects
OBJ = $(SRC:$(SRC_PATH)%.c=$(OBJ_PATH)%.o)

all: $(NAME)

$(OBJ_PATH)%.o: $(SRC_PATH)%.c | $(OBJ_PATH)
	@$(CC) $(CFLAGS) $(INC) -c $< -o $@

$(OBJ_PATH):
	@mkdir -p $(OBJ_PATH)

$(NAME): $(OBJ)
	@echo "Compiling \033[0;91m$(NAME)\033[0;0m..."
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJ)
	@echo "\033[0;91m$(NAME) \033[0;0mready."

bonus: all

clean:
	@echo "\033[0;0mRemoving \033[0;91m.o \033[0;0mobject files..."
	@rm -rf $(OBJ_PATH)
	@echo "\033[0;91m.o \033[0;0mobject files removed."

fclean: clean
	@echo "\033[0;0mRemoving \033[0;91m$(NAME)\033[0;0m..."
	@rm -f $(NAME)
	@echo "\033[0;91m$(NAME) \033[0;0mfile removed."

re: fclean all

.PHONY: all re clean fclean
