# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fmotte <fmotte@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/11/28 11:37:49 by cpollock          #+#    #+#              #
#    Updated: 2025/12/12 15:54:00 by fmotte           ###   ########.fr        #
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
FILE_NAMES_GRAPHIC = 	angle_math \
						add_timer_ms \
						collision_check \
						door_check \
						draw_arrow \
						draw_basic \
						draw_minimap \
						dtrig \
						init_imgs \
						is_raycast_hztl \
						key_events \
						kill_game \
						loop_event \
						main \
						player \
						player_collision \
						point_math \
						raycast \
						render_get_img \
						render \
						texture_read \
						vect_math

FILE_NAMES_PARSING = 	check_colour \
						check_map \
						check_map2 \
						check_map_path \
						check_map_path2 \
						check_texture \
						check_texture2 \
						check_texture3 \
						ft_realloc \
						ft_split \
						ft_transpose \
						mini_libft \
						mini_libft2 \
						mini_libft3 \
						parsing \
						parsing2 \
						parsing3 \
						stack \
						tab_utils
				
# =======================================
#              VARIABLE
# =======================================
FILE_NAMES = $(FILE_NAMES_GRAPHIC)	$(FILE_NAMES_PARSING)	
SRC_PATH = src
OBJ_PATH = obj
HEA_PATH = include


# Construire les chemins SRC automatiquement
SRC_GRAPHIC = $(FILE_NAMES_GRAPHIC:%=$(SRC_PATH)/graphic/%.c)
SRC_PARSING = $(FILE_NAMES_PARSING:%=$(SRC_PATH)/parsing/%.c)

SRC_FILES = $(SRC_GRAPHIC) $(SRC_PARSING)
OBJ_FILES = $(FILE_NAMES:%=$(OBJ_PATH)/%.o)
DEP_FILES = $(OBJ_FILES:.o=.d)
HEA_FILES = $(HEA_PATH)/cub3d.h

INCLUDE = -I $(HEA_PATH) -I gnl/include -I/usr/include -Imlx
ARCHIVE =  -L gnl -l gnl

MLX_GIT = https://github.com/42Paris/minilibx-linux.git
MLX_PATH = mlx
MLX_HEAD = $(MLX_PATH)/mlx.h

NAME = cub3d


# =======================================
#              COMPILATION
# =======================================
$(OBJ_PATH)/%.o: $(SRC_PATH)/graphic/%.c $(HEA_FILES) | $(OBJ_PATH) $(MLX_HEAD)
	$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

$(OBJ_PATH)/%.o: $(SRC_PATH)/parsing/%.c $(HEA_FILES) | $(OBJ_PATH) $(MLX_HEAD)
	$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@
	
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