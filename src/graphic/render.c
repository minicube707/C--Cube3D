/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpollock <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 15:09:50 by cpollock          #+#    #+#             */
/*   Updated: 2025/12/10 15:09:52 by cpollock         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void		draw_wall_line(t_game *data, t_raydata *ray, int i);
static int		get_img_x(t_game *data, t_raydata *ray, t_img *img);
static int		get_img_y(t_raydata *ray, t_img *img);
static double	fix_dist(double dist, double player_angle, double ray_angle);

void	render_raycast(t_game *data, t_player player)
{
	int			i;
	int			ceil_y;
	t_raydata	ray;

	i = 0;
	ray.angle = player.direction - (player.fov / 2);
	while (i < W_WIDTH)
	{
		ray.wall_side = raycast(data, &ray.vect, angle_limit(ray.angle), true);
		ray.dist = vect_dist(player.pos, ray.vect);
		ray.dist = fix_dist(ray.dist, player.direction, ray.angle);
		ray.height = (TILE_LEN / ray.dist) * (W_WIDTH);
		ray.start_y = (W_HEIGHT - ray.height) / 2;
		ray.end = ray.start_y + ray.height;
		ceil_y = 0;
		while (ceil_y < ray.start_y)
			draw_pixel(data, i, ceil_y++, data->col_ceil);
		draw_wall_line(data, &ray, i);
		while (ray.start_y < W_HEIGHT)
			draw_pixel(data, i, (ray.start_y)++, data->col_floor);
		ray.angle += player.fov / W_WIDTH;
		i++;
	}
}

static void	draw_wall_line(t_game *data, t_raydata *ray, int i)
{
	int		img_x;
	int		img_y;
	int		color;
	t_img	*img_use;

	img_use = render_get_img(data, ray);
	img_x = get_img_x(data, ray, img_use);
	while (ray->start_y < ray->end)
	{
		img_y = get_img_y(ray, img_use);
		color = get_img_pixel_col(img_use, img_x, img_y);
		draw_pixel(data, i, ray->start_y, color);
		ray->start_y += 1;
	}
}

static int	get_img_x(t_game *data, t_raydata *ray, t_img *img)
{
	double	img_x;

	img_x = 0;
	if (ray->wall_side == 1)
		img_x = TILE_LEN - fmod(ray->vect.x, TILE_LEN);
	if (ray->wall_side == 2)
		img_x = fmod(ray->vect.x, TILE_LEN);
	if (ray->wall_side == 3)
		img_x = TILE_LEN - fmod(ray->vect.y, TILE_LEN);
	if (ray->wall_side == 4)
		img_x = fmod(ray->vect.y, TILE_LEN);
	img_x = (img_x / TILE_LEN) * img->img_width;
	return ((int)img_x + door_img_x_add(data, *ray, *img));
}

static int	get_img_y(t_raydata *ray, t_img *img)
{
	double	img_y;
	double	dist_from_end;

	dist_from_end = ray->height - (ray->end - ray->start_y);
	img_y = (dist_from_end / ray->height) * img->img_height;
	return ((int)img_y);
}

static double	fix_dist(double dist, double player_angle, double ray_angle)
{
	double	angle_diff;

	angle_diff = angle_limit(player_angle - ray_angle);
	return (dist * dcos(angle_diff));
}
