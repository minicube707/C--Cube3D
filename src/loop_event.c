/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop_event.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmotte <fmotte@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/28 15:29:25 by cpollock          #+#    #+#             */
/*   Updated: 2025/12/02 15:20:31 by fmotte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void		raycast_test(t_game *data, int color);
static double	fix_dist(double dist, double player_angle, double ray_angle);

int	loop_event(t_game *data)
{
	struct timeval	time_check;
	double	time_diff;

	gettimeofday(&time_check, NULL);
	time_diff = (time_check.tv_sec * 1000) + (time_check.tv_usec / 1000);
	time_diff -= (data->time_frame.tv_sec * 1000) + (data->time_frame.tv_usec / 1000);
	if (time_diff > 1000/60)
	{
		data->time_frame.tv_sec = time_check.tv_sec;
		data->time_frame.tv_usec = time_check.tv_usec;
		if (data->player.key_space_pressed)
			door_check(data, &data->player);
		data->player.key_space_pressed = false;
		turn_player(&data->player);
		move_player(data, &data->player);
		raycast_test(data, 0x0000FF);
		draw_minimap(data);
		mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
	}
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
		wall_side = raycast(data, &ray_vect, angle_limit(ray_angle), true);
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
			if (vect_get_tile(data, ray_vect) == 'D')
				color = 0xFF0280;
		}
		double dist = vect_dist(data->player.pos, ray_vect);
		dist = fix_dist(dist, data->player.direction, ray_angle);
		double height = (TILE_LEN / dist) * (W_WIDTH);
		double start_y = (W_HEIGHT - height) / 2;
		double end = start_y + height;
		double ceil_y = 0;
		while (ceil_y < start_y)
		{
			draw_pixel(data, i, ceil_y, data->col_ceil);
			ceil_y += 1;
		}
		while (start_y < end)
		{
			draw_pixel(data, i, start_y, color);
			start_y += 1;
		}
		while (start_y < W_HEIGHT)
		{
			draw_pixel(data, i, start_y, data->col_floor);
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
