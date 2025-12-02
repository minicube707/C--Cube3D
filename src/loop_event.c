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

static void	draw_grid(t_game *data);
static void	raycast_test(t_game *data, t_vector plane_l, t_vector plane_r, int color);

int	loop_event(t_game *data)
{
	t_rectangle	player_square;
	t_vector	dir_vect;
	t_vector	plane_l_vect;
	t_vector	plane_r_vect;

	draw_grid(data);
	player_square.x = data->player.pos.x - (data->player.box_width / 2);
	player_square.y = data->player.pos.y - (data->player.box_width / 2);
	player_square.width = data->player.box_width;
	player_square.height = data->player.box_width;
	draw_rectangle(data, player_square, 0);
	dir_vect.x = data->player.pos.x + dcos(data->player.direction) * data->player.plane_dist;
	dir_vect.y = data->player.pos.y + dsin(data->player.direction) * data->player.plane_dist;
	draw_line(data, data->player.pos, dir_vect, 0);
	plane_l_vect.x = dir_vect.x - dcos(data->player.direction + 90) * dtan(data->player.fov / 2) * data->player.plane_dist;
	plane_l_vect.y = dir_vect.y - dsin(data->player.direction + 90) * dtan(data->player.fov / 2) * data->player.plane_dist;
	plane_r_vect.x = dir_vect.x + dcos(data->player.direction + 90) * dtan(data->player.fov / 2) * data->player.plane_dist;
	plane_r_vect.y = dir_vect.y + dsin(data->player.direction + 90) * dtan(data->player.fov / 2) * data->player.plane_dist;
	draw_line(data, plane_l_vect, plane_r_vect, 0);
	raycast_test(data, plane_l_vect, plane_r_vect, 0);
	turn_player(&data->player);
	move_player(&data->player);
	player_square.x = data->player.pos.x - (data->player.box_width / 2);
	player_square.y = data->player.pos.y - (data->player.box_width / 2);
	draw_rectangle(data, player_square, 0x00FF00);
	dir_vect.x = data->player.pos.x + dcos(data->player.direction) * data->player.plane_dist;
	dir_vect.y = data->player.pos.y + dsin(data->player.direction) * data->player.plane_dist;
	draw_line(data, data->player.pos, dir_vect, 0x0000FF);
	plane_l_vect.x = dir_vect.x - dcos(data->player.direction + 90) * dtan(data->player.fov / 2) * data->player.plane_dist;
	plane_l_vect.y = dir_vect.y - dsin(data->player.direction + 90) * dtan(data->player.fov / 2) * data->player.plane_dist;
	plane_r_vect.x = dir_vect.x + dcos(data->player.direction + 90) * dtan(data->player.fov / 2) * data->player.plane_dist;
	plane_r_vect.y = dir_vect.y + dsin(data->player.direction + 90) * dtan(data->player.fov / 2) * data->player.plane_dist;
	draw_line(data, plane_l_vect, plane_r_vect, 0x0000FF);
	raycast_test(data, plane_l_vect, plane_r_vect, 0x0000FF);
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

static void	raycast_test(t_game *data, t_vector plane_l, t_vector plane_r, int color)
{
	double		i;
	double		ray_dist;
	double		plane_dist;
	double		plane_ang;
	t_vector	ray_start;
	t_vector	ray_end;

	i = 0;
	ray_dist = 200;
	plane_dist = vect_dist(plane_l, plane_r);
	plane_ang = vect_angle(plane_l, plane_r);
	while (i <= plane_dist)
	{
		vect_add(&ray_start, plane_l, plane_ang, i);
		vect_add(&ray_end, data->player.pos, vect_angle(data->player.pos, ray_start), ray_dist);
		draw_line(data, ray_start, ray_end, color);
		i += plane_dist / W_WIDTH;
	}
}
