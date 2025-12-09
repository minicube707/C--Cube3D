# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fmotte <fmotte@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/11/28 11:37:49 by cpollock          #+#    #+#              #
#    Updated: 2025/12/09 13:50:48 by fmotte           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# =======================================
#            MAKEFILE PROJET
# =======================================

# =======================================
#                FLAGS
# =======================================
CC = cc
CFLAGS = -Wall -Wextra -Werror -MMD -MP -g 

# =======================================
#              FILE
# =======================================
FILE_NAMES = 	angle_math \
				check_colour \
				check_map2 \
				check_map \
				check_map_path2 \
				check_map_path \
				check_texture \
				collision_check \
				draw_arrow \
				draw_basic \
				draw_minimap \
				dtrig \
				ft_realloc \
				ft_split \
				ft_transpose \
				key_events \
				loop_event \
				main \
				mini_libft2 \
				mini_libft \
				parsing2 \
				parsing \
				player \
				player_collision \
				point_math \
				raycast \
				stack \
				tab_utils \
				vect_math

# =======================================
#              VARIABLE
# =======================================	
SRC_PATH = src
OBJ_PATH = obj
HEA_PATH = include

SRC_FILES = $(FILE_NAMES:%=$(SRC_PATH)/%.c)
OBJ_FILES = $(FILE_NAMES:%=$(OBJ_PATH)/%.o)
DEP_FILES = $(OBJ_FILES:.o=.d)
HEA_FILES = $(HEA_PATH)/cub3d.h

INCLUDE = -I $(HEA_PATH) -I gnl/include
ARCHIVE =  -L gnl -l gnl

MLX_GIT = https://github.com/42Paris/minilibx-linux.git
MLX_PATH = mlx
MLX_HEAD = $(MLX_PATH)/mlx.h

NAME = cub3d

# =======================================
#              RULES
# =======================================
all: $(NAME)

bonus: all

.PHONY: all clean fclean re bonus

$(OBJ_PATH) :
	mkdir -p $(OBJ_PATH)
	
$(NAME): $(OBJ_FILES) $(MLX_HEAD)
	@$(MAKE) -s -C gnl
	$(CC) $(CFLAGS) $(OBJ_FILES) $(ARCHIVE) -Lmlx -lmlx -L/usr/lib -Imlx -lXext -lX11 -lm -lz -o $(NAME)

$(OBJ_PATH)/%.o: $(SRC_PATH)/%.c $(HEA_FILES) | $(OBJ_PATH) $(MLX_HEAD)
	$(CC) $(CFLAGS) $(INCLUDE)  -I/usr/include -Imlx -O3 -c $< -o $@

$(MLX_HEAD):
	git clone $(MLX_GIT) $(MLX_PATH)
	make -C $(MLX_PATH)

clean:
	@$(MAKE) -s -C gnl fclean
	rm -f $(OBJ_FILES) $(DEP_FILES)
	rm -rf $(OBJ_PATH)

fclean: clean
	rm -f $(NAME)

re: fclean all

reset: fclean
	rm -rf $(MLX_PATH)

# Inclusion automatique des fichiers .d s’ils existent
-include $(DEP_FILES)