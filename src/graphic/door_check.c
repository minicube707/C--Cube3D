/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door_check.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpollock <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 12:34:52 by cpollock          #+#    #+#             */
/*   Updated: 2025/12/10 12:35:00 by cpollock         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	door_close(t_game *data, t_player *player, t_coord crd);

void	door_check(t_game *data, t_player *player)
{
	t_vector	vect_check;
	t_coord		coord_check;
	char		tile_check;

	vect_add(&vect_check, player->pos, deg2rad(player->direction),
		TILE_LEN / 2);
	tile_check = vect_get_tile(data, vect_check);
	while (tile_check != 'D' && tile_check != 'O'
		&& vect_dist(player->pos, vect_check) <= TILE_LEN * 1.5)
	{
		vect_add(&vect_check, vect_check, deg2rad(player->direction),
			TILE_LEN / 2);
		tile_check = vect_get_tile(data, vect_check);
	}
	if (tile_check == 'D' || tile_check == 'O')
	{
		vect_to_mapcoord(vect_check, &coord_check);
		if (tile_check == 'D')
		{
			data->map[coord_check.x][coord_check.y] = 'O';
		}
		else
			door_close(data, player, coord_check);
	}
}

static void	door_close(t_game *data, t_player *player, t_coord crd)
{
	data->map[crd.x][crd.y] = 'D';
	if (player_in_wall(data, *player))
		data->map[crd.x][crd.y] = 'O';
}
