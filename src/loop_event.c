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

static void		raycast_test(t_game *data, int color);
static double	fix_dist(double dist, double player_angle, double ray_angle);
static void		wall_test(t_game *data);

int	loop_event(t_game *data)
{
	t_rectangle	player_square;
	t_vector	dir_vect;

	player_square.x = data->player.pos.x - (data->player.box_width / 2);
	player_square.y = data->player.pos.y - (data->player.box_width / 2);
	player_square.width = data->player.box_width;
	player_square.height = data->player.box_width;
	draw_rectangle(data, player_square, 0);
	dir_vect.x = data->player.pos.x + dcos(data->player.direction) * 11;
	dir_vect.y = data->player.pos.y + dsin(data->player.direction) * 11;
	draw_line(data, data->player.pos, dir_vect, 0);
	raycast_test(data, 0);
	turn_player(&data->player);
	move_player(&data->player);
	player_square.x = data->player.pos.x - (data->player.box_width / 2);
	player_square.y = data->player.pos.y - (data->player.box_width / 2);
	draw_rectangle(data, player_square, 0x00FF00);
	dir_vect.x = data->player.pos.x + dcos(data->player.direction) * 11;
	dir_vect.y = data->player.pos.y + dsin(data->player.direction) * 11;
	draw_line(data, data->player.pos, dir_vect, 0x0000FF);
	wall_test(data);
	raycast_test(data, 0x0000FF);
	mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
	return (0);
}

static void	raycast_test(t_game *data, int color)
{
	int			i;
	int			wall_side;
	double		ray_angle;
	t_vector	ray_vect;

	i = 0;
	ray_angle = data->player.direction - (data->player.fov / 2);
	while (i < W_WIDTH)
	{
		wall_side = raycast(data, &ray_vect, angle_limit(ray_angle));
		if (color != 0)
		{
			if (wall_side == 1)
				color = 0x0000FF;
			if (wall_side == 2)
				color = 0x000280;
			if (wall_side == 3)
				color = 0x0066FF;
			if (wall_side == 4)
				color = 0x0044AA;
		}
		double dist = vect_dist(data->player.pos, ray_vect);
		dist = fix_dist(dist, data->player.direction, ray_angle);
		double height = (TILE_LEN / dist) * (W_WIDTH);
		double start_y = (W_HEIGHT - height) / 2;
		double end = start_y + height;
		while (start_y < end)
		{
			draw_pixel(data, i, start_y, color);
			start_y += 1;
		}
		ray_angle += data->player.fov / W_WIDTH;
		i++;
	}
}

static double	fix_dist(double dist, double player_angle, double ray_angle)
{
	double	angle_diff;

	angle_diff = angle_limit(player_angle - ray_angle);
	return (dist * dcos(angle_diff));
}

static void	wall_test(t_game *data)
{
	int			i;
	int			j;
	t_rectangle	wall_rect;

	i = 0;
	wall_rect.width = TILE_LEN;
	wall_rect.height = TILE_LEN;
	while ((data->map)[i] != NULL)
	{
		j = 0;
		while ((data->map)[i][j] != '\0')
		{
			if ((data->map)[i][j] == '1')
			{
				wall_rect.x = i * TILE_LEN;
				wall_rect.y = j * TILE_LEN;
				draw_rectangle(data, wall_rect, 0x850000);
			}
			j++;
		}
		i++;
	}
}
