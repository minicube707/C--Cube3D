/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_collision.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmotte <fmotte@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/05 11:41:34 by cpollock          #+#    #+#             */
/*   Updated: 2025/12/08 14:57:41 by fmotte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	move_collision_x(t_game *data, t_player *player, double spd);
static void	move_collision_y(t_game *data, t_player *player, double spd);

void	move_collision(t_game *data, t_player *player,
			double x_spd, double y_spd)
{
	if (player_in_wall(data, *player))
	{
		player->pos.x += x_spd;
		player->pos.y += y_spd;
		return ;
	}
	move_collision_x(data, player, x_spd);
	move_collision_y(data, player, y_spd);
}

static void	move_collision_x(t_game *data, t_player *player, double spd)
{
	double	sgn;
	double	back;

	player->pos.x += spd;
	if (spd != 0 && player_in_wall(data, *player))
	{
		sgn = (spd > 0) - (spd < 0);
		back = -fmod(player->pos.x + (player->box_width / 2) * sgn, TILE_LEN);
		if (sgn > 0)
			player->pos.x += back - 0.0001;
		else
			player->pos.x += TILE_LEN + back;
		while (player_in_wall(data, *player))
			player->pos.x -= TILE_LEN * sgn;
	}
}

static void	move_collision_y(t_game *data, t_player *player, double spd)
{
	double	sgn;
	double	back;

	player->pos.y += spd;
	if (spd != 0 && player_in_wall(data, *player))
	{
		sgn = (spd > 0) - (spd < 0);
		back = -fmod(player->pos.y + (player->box_width / 2) * sgn, TILE_LEN);
		if (sgn > 0)
			player->pos.y += back - 0.0001;
		else
			player->pos.y += TILE_LEN + back;
		while (player_in_wall(data, *player))
			player->pos.y -= TILE_LEN * sgn;
	}
}
