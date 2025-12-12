/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collision_check.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmotte <fmotte@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 14:34:33 by cpollock          #+#    #+#             */
/*   Updated: 2025/12/08 14:56:57 by fmotte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static bool	vect_in_open(t_game *data, t_vector point);

bool	vect_in_wall(t_game *data, t_vector point)
{
	char	tile;

	tile = vect_get_tile(data, point);
	if (tile == 0 || tile == '1' || tile == 'D')
		return (true);
	return (false);
}

bool	player_in_wall(t_game *data, t_player player)
{
	t_vector	check_vect;

	check_vect.x = player.pos.x - (player.box_width / 2);
	check_vect.y = player.pos.y - (player.box_width / 2);
	if (vect_in_wall(data, check_vect) || vect_in_open(data, check_vect))
		return (true);
	check_vect.x += player.box_width;
	if (vect_in_wall(data, check_vect) || vect_in_open(data, check_vect))
		return (true);
	check_vect.y += player.box_width;
	if (vect_in_wall(data, check_vect) || vect_in_open(data, check_vect))
		return (true);
	check_vect.x -= player.box_width;
	if (vect_in_wall(data, check_vect) || vect_in_open(data, check_vect))
		return (true);
	return (false);
}

char	vect_get_tile(t_game *data, t_vector point)
{
	t_coord	check_coord;

	vect_to_mapcoord(point, &check_coord);
	if ((check_coord.x < 0 || check_coord.x >= data->map_width)
		|| (check_coord.y < 0 || check_coord.y >= data->map_height))
		return (0);
	return ((data->map)[check_coord.x][check_coord.y]);
}

void	vect_to_mapcoord(t_vector point, t_coord *map_coord)
{
	map_coord->x = (int)floor(point.x / TILE_LEN);
	map_coord->y = (int)floor(point.y / TILE_LEN);
}

static bool	vect_in_open(t_game *data, t_vector point)
{
	char	map_tile;
	t_coord	map_coord;

	map_tile = vect_get_tile(data, point);
	if (map_tile == 'O')
	{
		vect_to_mapcoord(point, &map_coord);
		return ((data->door_state)[map_coord.x][map_coord.y] > 0);
	}
	return (false);
}
