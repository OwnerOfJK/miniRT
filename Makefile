# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ecarlier <ecarlier@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/20 14:04:55 by jkaller           #+#    #+#              #
#    Updated: 2024/08/05 14:51:31 by ecarlier         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Name of the target executable
NAME = miniRT

# Compiler
CC = cc

# Compiler flags
CFLAGS = -Wall -Werror -Wextra -Imlx -g

# MLX flags for linking mlx_linux library
MLXFLAGS = -L ./libs/mlx_linux -lmlx -lXext -lX11 -lm

# Library files
LIBS = ./libs/libft/libft.a

# Source files
SRCS = src/main.c $(wildcard src/error/*.c) $(wildcard src/parser/*.c) $(wildcard src/free/*.c) $(wildcard src/utils/*.c) $(wildcard src/raytracing/*.c) $(wildcard src/tests/*.c) \
	$(wildcard src/utils/matrices/*.c) $(wildcard src/utils/intersections/*.c) $(wildcard src/utils/rays/*.c) $(wildcard src/utils/parsing/*.c) $(wildcard src/utils/light/*.c) \
	$(wildcard src/utils/linked_lists/*.c) $(wildcard src/init/*.c) $(wildcard src/utils/vectors/*.c)

# Object files
OBJS = $(SRCS:.c=.o)
%.o: %.c
		@${CC} ${CFLAGS} -c $< -o $@

# Build the target executable
all: $(NAME)

$(NAME): $(OBJS)
	@echo "Building mlx_linux and libft targets..."
	@make -s -C ./libs/mlx_linux 2> /dev/null > /dev/null
	@make -s -C ./libs/libft > /dev/null
	@echo "Linking the executable..."
	@$(CC) $(CFLAGS) $(OBJS) $(LIBS) $(MLXFLAGS) -o $(NAME)
	@echo "Build completed!"

clean:
	@echo "Cleaning mlx_linux and libft targets..."
	@make clean -C ./libs/mlx_linux > /dev/null
	@make clean -C ./libs/libft > /dev/null
	@echo "Removing object files..."
	@rm -rf $(OBJS)

# Remove all generated files
fclean:
	@echo "Performing full clean on mlx_linux and libft targets..."
	@make clean -C  ./libs/mlx_linux > /dev/null
	@make fclean -C  ./libs/libft > /dev/null
	@echo "Removing object files and the target executable..."
	@rm -rf $(OBJS)
	@rm -rf $(NAME)

# Rebuild the project
re: fclean all

# Specify the phony targets
.PHONY: all clean fclean re
