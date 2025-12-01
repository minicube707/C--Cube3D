# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cpollock <cpollock@42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/11/28 11:37:49 by cpollock          #+#    #+#              #
#    Updated: 2025/11/28 11:38:08 by cpollock         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3d

CC = cc
CFLAGS = -Wall -Wextra -Werror

SRCDIR = src/
SOURCES = main.c \
		  player.c \
		  draw_basic.c \
		  triangle_math.c \
		  loop_event.c

OBJDIR = obj/
OBJECTS = $(addprefix $(OBJDIR), $(SOURCES:.c=.o))

MLX_GIT = https://github.com/42Paris/minilibx-linux.git
MLX_DIR = mlx
MLXH = $(MLX_DIR)/mlx.h

all: $(NAME)

bonus: all

$(NAME): $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -Lmlx -lmlx -L/usr/lib -Imlx -lXext -lX11 -lm -lz -o $(NAME)

$(OBJECTS): $(OBJDIR)%.o: $(SRCDIR)%.c $(MLXH)
	$(CC) $(CFLAGS) -I/usr/include -Imlx -O3 -c $< -o $@

$(MLXH):
	git clone $(MLX_GIT) $(MLX_DIR)
	make -C $(MLX_DIR)

clean:
	rm -f $(OBJECTS)

fclean: clean
	rm -f $(NAME)

re: fclean all