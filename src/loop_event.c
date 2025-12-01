/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop_event.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpollock <cpollock@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/28 15:29:25 by cpollock          #+#    #+#             */
/*   Updated: 2025/11/28 15:29:40 by cpollock         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static void	draw_grid(t_game *data);

int	loop_event(t_game *data)
{
	t_rectangle	player_square;
	t_vector	dir_vect;

	draw_grid(data);
	player_square.x = data->player.pos.x - (data->player.box_width / 2);
	player_square.y = data->player.pos.y - (data->player.box_width / 2);
	player_square.width = data->player.box_width;
	player_square.height = data->player.box_width;
	draw_rectangle(data, player_square, 0);
	dir_vect.x = data->player.pos.x + cos(deg2rad(data->player.direction)) * 100;
	dir_vect.y = data->player.pos.y + sin(deg2rad(data->player.direction)) * 100;
	draw_line(data, data->player.pos, dir_vect, 0);
	turn_player(&data->player);
	move_player(&data->player);
	player_square.x = data->player.pos.x - (data->player.box_width / 2);
	player_square.y = data->player.pos.y - (data->player.box_width / 2);
	draw_rectangle(data, player_square, 0x00FF00);
	dir_vect.x = data->player.pos.x + cos(deg2rad(data->player.direction)) * 100;
	dir_vect.y = data->player.pos.y + sin(deg2rad(data->player.direction)) * 100;
	draw_line(data, data->player.pos, dir_vect, 0x0000FF);
	mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
	return (0);
}

static void	draw_grid(t_game *data)
{
	t_vector	vct1;
	t_vector	vct2;

	vct1.x = TILE_LEN;
	vct2.x = vct1.x;
	vct1.y = 0;
	vct2.y = W_HEIGHT;
	while (vct1.x < W_WIDTH)
	{
		draw_line(data, vct1, vct2, 0x002E10);
		vct1.x += TILE_LEN;
		vct2.x = vct1.x;
	}
	vct1.y = TILE_LEN;
	vct2.y = vct1.y;
	vct1.x = 0;
	vct2.x = W_WIDTH;
	while (vct1.y < W_HEIGHT)
	{
		draw_line(data, vct1, vct2, 0x002E10);
		vct1.y += TILE_LEN;
		vct2.y = vct1.y;
	}
}
