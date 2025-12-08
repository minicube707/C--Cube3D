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

bool	vect_in_wall(t_game *data, t_vector point)
{
	int	check_x;
	int	check_y;

	check_x = (int)floor(point.x / TILE_LEN);
	check_y = (int)floor(point.y / TILE_LEN);
	if ((check_x < 0 || check_x >= data->map_width)
		|| (check_y < 0 || check_y >= data->map_height)
		|| (data->map)[check_x][check_y] == '1')
		return (true);
	return (false);
}

bool	player_in_wall(t_game *data, t_player player)
{
	t_vector	check_vect;

	check_vect.x = player.pos.x - (player.box_width / 2);
	check_vect.y = player.pos.y - (player.box_width / 2);
	if (vect_in_wall(data, check_vect))
		return (true);
	check_vect.x += player.box_width;
	if (vect_in_wall(data, check_vect))
		return (true);
	check_vect.y += player.box_width;
	if (vect_in_wall(data, check_vect))
		return (true);
	check_vect.x -= player.box_width;
	if (vect_in_wall(data, check_vect))
		return (true);
	return (false);
}
