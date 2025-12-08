/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmotte <fmotte@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 14:10:27 by cpollock          #+#    #+#             */
/*   Updated: 2025/12/08 14:57:50 by fmotte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	raycast_hztl(t_game *data, t_vector *ray_vect, double angle);
static void	set_ray_hztl(t_game *data, t_vector *ray_vect, double angle);
static void	raycast_vtcl(t_game *data, t_vector *ray_vect, double angle);
static void	set_ray_vtcl(t_game *data, t_vector *ray_vect, double angle);

int	raycast(t_game *data, t_vector *ray_vect, double angle)
{
	t_vector	ray_hztl;
	t_vector	ray_vtcl;

	raycast_hztl(data, &ray_hztl, angle);
	raycast_vtcl(data, &ray_vtcl, angle);
	if (vect_dist(data->player.pos, ray_hztl)
		<= vect_dist(data->player.pos, ray_vtcl))
	{
		ray_vect->x = ray_hztl.x;
		ray_vect->y = ray_hztl.y;
		if (ray_vect->y > data->player.pos.y)
			return (1);
		return (2);
	}
	else
	{
		ray_vect->x = ray_vtcl.x;
		ray_vect->y = ray_vtcl.y;
		if (ray_vect->x > data->player.pos.x)
			return (3);
		return (4);
	}
}

static void	raycast_hztl(t_game *data, t_vector *ray_vect, double angle)
{
	double		x_offset;
	double		y_offset;
	double		a_tan;

	set_ray_hztl(data, ray_vect, angle);
	a_tan = -(1 / dtan(angle));
	y_offset = TILE_LEN;
	if (angle > 180)
		y_offset = -y_offset;
	x_offset = -(y_offset * a_tan);
	while (!vect_in_wall(data, *ray_vect))
	{
		ray_vect->x += x_offset;
		ray_vect->y += y_offset;
	}
}

static void	set_ray_hztl(t_game *data, t_vector *ray_vect, double angle)
{
	t_vector	start_vect;
	double		a_tan;

	start_vect = data->player.pos;
	a_tan = -(1 / dtan(angle));
	if (angle > 180)
	{
		ray_vect->y = start_vect.y - fmod(start_vect.y, TILE_LEN) - 0.0001;
		ray_vect->x = (start_vect.y - ray_vect->y) * a_tan + start_vect.x;
	}
	if (angle < 180)
	{
		ray_vect->y = start_vect.y + (TILE_LEN - fmod(start_vect.y, TILE_LEN));
		ray_vect->x = (start_vect.y - ray_vect->y) * a_tan + start_vect.x;
	}
	if (angle == 0 || angle == 180)
	{
		vect_add(ray_vect, start_vect, angle / 180 * PI,
			point_dist(0, 0, data->map_width, data->map_height) * TILE_LEN);
	}
}

static void	raycast_vtcl(t_game *data, t_vector *ray_vect, double angle)
{
	double		x_offset;
	double		y_offset;
	double		n_tan;

	set_ray_vtcl(data, ray_vect, angle);
	n_tan = -dtan(angle);
	x_offset = TILE_LEN;
	if (angle > 90 && angle < 270)
		x_offset = -x_offset;
	y_offset = -(x_offset * n_tan);
	while (!vect_in_wall(data, *ray_vect))
	{
		ray_vect->x += x_offset;
		ray_vect->y += y_offset;
	}
}

static void	set_ray_vtcl(t_game *data, t_vector *ray_vect, double angle)
{
	t_vector	start_vect;
	double		n_tan;

	start_vect = data->player.pos;
	n_tan = -dtan(angle);
	if (angle > 90 && angle < 270)
	{
		ray_vect->x = start_vect.x - fmod(start_vect.x, TILE_LEN) - 0.0001;
		ray_vect->y = (start_vect.x - ray_vect->x) * n_tan + start_vect.y;
	}
	if (angle < 90 || angle > 270)
	{
		ray_vect->x = start_vect.x + (TILE_LEN - fmod(start_vect.x, TILE_LEN));
		ray_vect->y = (start_vect.x - ray_vect->x) * n_tan + start_vect.y;
	}
	if (angle == 90 || angle == 270)
	{
		vect_add(ray_vect, start_vect, angle / 180 * PI,
			point_dist(0, 0, data->map_width, data->map_height) * TILE_LEN);
	}
}
