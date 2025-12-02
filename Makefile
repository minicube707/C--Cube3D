# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fmotte <fmotte@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/11/28 11:37:49 by cpollock          #+#    #+#              #
#    Updated: 2025/12/02 14:09:42 by fmotte           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3d

CC = cc
CFLAGS = -Wall -Wextra -Werror

FILE_NAMES = 	main \
		  		setup_map \
		  		player \
		  		draw_basic \
		  		dtrig \
		  		point_math \
		  		vect_math \
		  		loop_event

SRC_PATH = src
OBJ_PATH = obj
HEA_PATH = include

SRC_FILES = $(FILE_NAMES:%=$(SRC_PATH)/%.c)
OBJ_FILES = $(FILE_NAMES:%=$(OBJ_PATH)/%.o)
HEA_FILES = $(HEA_PATH)/cub3d.h

MLX_GIT = https://github.com/42Paris/minilibx-linux.git
MLX_PATH = mlx
MLX_HEAD = $(MLX_PATH)/mlx.h

all: $(NAME)

bonus: all

.PHONY: all clean fclean re bonus

$(OBJ_PATH) :
	mkdir -p $(OBJ_PATH)
	
$(NAME): $(OBJ_FILES) $(MLX_HEAD)
	$(CC) $(CFLAGS) $(OBJ_FILES) -Lmlx -lmlx -L/usr/lib -Imlx -lXext -lX11 -lm -lz -o $(NAME)

$(OBJ_PATH)/%.o: $(SRC_PATH)/%.c $(HEA_FILES) | $(OBJ_PATH) $(MLX_HEAD)
	$(CC) $(CFLAGS) -I/usr/include -Imlx -O3 -c $< -o $@

$(MLX_HEAD):
	git clone $(MLX_GIT) $(MLX_PATH)
	make -C $(MLX_PATH)

clean:
	rm -f $(OBJ_FILES)
	rm -rf $(OBJ_PATH)

fclean: clean
	rm -f $(NAME)

re: fclean all

reset: fclean
	rm -rf $(MLX_PATH)