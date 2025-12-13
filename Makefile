# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fmotte <fmotte@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/11/28 11:37:49 by cpollock          #+#    #+#              #
#    Updated: 2025/12/13 15:28:56 by fmotte           ###   ########.fr        #
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
						door_anim \
						door_check \
						draw_arrow \
						draw_basic \
						draw_minimap \
						dtrig \
						init_game \
						init_imgs \
						is_raycast_hztl \
						key_events \
						kill_game \
						loop_event \
						main \
						player \
						player_collision \
						point_math \
						ray_collision \
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

ANIMATION_SCRIPY = ./animation.sh  # Le script spinner

# =======================================
#            COLOR
# =======================================
RESET       = \033[0m
BOLD        = \033[1m
RED         = \033[31m
GREEN       = \033[32m
YELLOW      = \033[38;5;227m
BLUE        = \033[38;5;26m
MAGENTA    =  \033[35m
CYAN        = \033[38;5;51m	

# =======================================
#              COMPILATION
# =======================================
$(OBJ_PATH)/%.o: $(SRC_PATH)/graphic/%.c $(HEA_FILES) | $(OBJ_PATH) $(MLX_HEAD)
	@$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

$(OBJ_PATH)/%.o: $(SRC_PATH)/parsing/%.c $(HEA_FILES) | $(OBJ_PATH) $(MLX_HEAD)
	@$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@


# =======================================
#              RULES
# =======================================
all: $(NAME)

bonus: all

.PHONY: all clean fclean re bonus

$(OBJ_PATH) :
	@mkdir -p $(OBJ_PATH)
	
$(NAME): $(OBJ_FILES) $(MLX_HEAD)
	@$(MAKE) -s -C gnl 
	@stdbuf -o0 $(CC) $(CFLAGS) $(OBJ_FILES) $(ARCHIVE) -Lmlx -lmlx -L/usr/lib -Imlx -lXext -lX11 -lm -lz -o $(NAME) & pid=$!
	@$(ANIMATION_SCRIPY) $$pid

$(MLX_HEAD):
	@git clone $(MLX_GIT) $(MLX_PATH)
	@make -C $(MLX_PATH)

clean:
	@$(MAKE) -s -C gnl clean
	@echo "\n$(RED)$(NAME_FOLDER): 🧹 Suppression des fichiers objets...$(RESET)"
	@rm -f $(OBJ_FILES) $(DEP_FILES)
	@rm -rf $(OBJ_PATH)
	@echo "$(GREEN)$(NAME_FOLDER): ✅ Fichiers supprimés.$(RESET)"

fclean: clean
	@$(MAKE) -s -C gnl fclean
	@echo "\n$(RED)$(NAME_FOLDER): 🧹 Suppression des archive...$(RESET)"
	@rm -f $(NAME)
	@echo "$(GREEN)$(NAME_FOLDER): ✅ Fichiers supprimés.$(RESET)"

re: fclean all

reset: fclean
	@echo "\n$(RED)$(NAME_FOLDER): 🧹 Suppression de la MLX...$(RESET)"
	@rm -rf $(MLX_PATH)
	@echo "$(GREEN)$(NAME_FOLDER): ✅ Fichiers supprimés.$(RESET)"

# Inclusion automatique des fichiers .d s’ils existent
-include $(DEP_FILES)