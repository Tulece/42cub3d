# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tgibert <tgibert@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/20 22:17:24 by anporced          #+#    #+#              #
#    Updated: 2024/08/06 13:28:32 by tgibert          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	cub3D
CC		=	cc
FLAGS 	=	-g -Wall -Werror -Werror
LIBFT_PATH = libft/
LIBFT_FILE = libft/libft.a
MLX_PATH = minilibx-linux/libmlx.a
MLX_FILE = libmlx.a
MLX_FLAGS = -L/usr/X11R6/lib -lX11 -lXext -lm

SRC 	=	$(wildcard src/*.c)
OBJ 	=	$(patsubst %.c,%.o,$(SRC))
RM 		=	rm -f

.SUFFIXES: .c .o

$(NAME): $(OBJ)
	make -C minilibx-linux/
	make -C libft/
	$(CC) $(CFLAGS) $(OBJ) $(MLX_PATH) $(MLX_FLAGS) $(LIBFT_FILE) -o $(NAME) -I includes/

%.o: %.c
	$(CC) $(FLAGS) -c $< -o $@ -I includes/

all: $(NAME)

do_configure:
	echo "Configuring minilibx..."
	make -C minilibx-linux/ do_configure
	echo "Minilibx configuration complete."

clean:
	echo "Deleting Obj file in $(MLX_PATH)...\n"
	make clean -sC minilibx-linux/
	echo "Deleting Obj file in $(LIBFT_PATH)...\n"
	make clean -sC $(LIBFT_PATH)
	echo "Done\n"
	echo "Deleting cub3D object...\n"
	rm -f $(OBJ)
	echo "Done\n"

fclean: clean
	echo "Deleting cub3D executable..."
	rm -f $(NAME)
	make fclean -C $(LIBFT_PATH)
	echo "Done\n"

re: fclean all

.PHONY: all do_configure clean fclean re
