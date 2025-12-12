/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_collision.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpollock <cpollock@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/12 14:45:14 by cpollock          #+#    #+#             */
/*   Updated: 2025/12/12 14:45:25 by cpollock         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool	ray_collision(t_game *data, t_vector ray_vect, bool is_hztl)
{
	char	map_tile;
	t_coord	map_coord;
	double	door_percent;
	double	wall_percent;

	map_tile = vect_get_tile(data, ray_vect);
	if (map_tile != 'D' && map_tile != 'O')
		return (vect_in_wall(data, ray_vect));
	vect_to_mapcoord(ray_vect, &map_coord);
	door_percent = data->door_state[map_coord.x][map_coord.y];
	if (door_percent <= 0)
		return (false);
	if (is_hztl)
		wall_percent = fmod(ray_vect.x, TILE_LEN);
	else
		wall_percent = fmod(ray_vect.y, TILE_LEN);
	wall_percent = (wall_percent / TILE_LEN) * 100;
	return (wall_percent < door_percent);
}
