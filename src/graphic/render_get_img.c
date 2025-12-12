/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_get_img.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpollock <cpollock@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 11:01:51 by cpollock          #+#    #+#             */
/*   Updated: 2025/12/11 11:01:53 by cpollock         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	render_get_anim_index(t_game *data, t_raydata *ray);

t_img	*render_get_img(t_game *data, t_raydata *ray)
{
	t_img	*img_use;
	int		frame_use;
	char	map_tile;

	img_use = NULL;
	frame_use = render_get_anim_index(data, ray);
	map_tile = vect_get_tile(data, ray->vect);
	if (map_tile == 'D' || map_tile == 'O')
		img_use = &(data->wall_imgs.wall_door[frame_use]);
	else if (ray->wall_side == 1)
		img_use = &(data->wall_imgs.wall_north[frame_use]);
	else if (ray->wall_side == 2)
		img_use = &(data->wall_imgs.wall_south[frame_use]);
	else if (ray->wall_side == 3)
		img_use = &(data->wall_imgs.wall_east[frame_use]);
	else if (ray->wall_side == 4)
		img_use = &(data->wall_imgs.wall_west[frame_use]);
	return (img_use);
}

static int	render_get_anim_index(t_game *data, t_raydata *ray)
{
	int		frame_count;
	int		frame_at;
	char	map_tile;

	frame_count = 0;
	map_tile = vect_get_tile(data, ray->vect);
	if (map_tile == 'D' || map_tile == 'O')
		frame_count = data->wall_imgs.frames_door;
	else if (ray->wall_side == 1)
		frame_count = data->wall_imgs.frames_north;
	else if (ray->wall_side == 2)
		frame_count = data->wall_imgs.frames_south;
	else if (ray->wall_side == 3)
		frame_count = data->wall_imgs.frames_east;
	else if (ray->wall_side == 4)
		frame_count = data->wall_imgs.frames_west;
	frame_at = ((int)data->ms_anim * frame_count) / ANIM_MS;
	frame_at = frame_at % frame_count;
	return (frame_at);
}
