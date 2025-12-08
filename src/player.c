/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmotte <fmotte@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/28 12:57:20 by cpollock          #+#    #+#             */
/*   Updated: 2025/12/02 15:20:44 by fmotte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_player(t_player *player, double x, double y, double angle)
{
	player->pos.x = x;
	player->pos.y = y;
	player->direction = angle;
	player->fov = 60;
	player->key_up = false;
	player->key_down = false;
	player->key_left = false;
	player->key_right = false;
	player->key_turn_l = false;
	player->key_turn_r = false;
	player->key_sprint = false;
	player->box_width = TILE_LEN * 0.6;
	player->walk_spd = 2;
	player->turn_spd = 2;
}

void	move_player(t_game *data, t_player *player)
{
	double	spd;
	double	angle_add;

	if ((player->key_up ^ player->key_down)
		|| (player->key_left ^ player->key_right))
	{
		spd = player->walk_spd;
		spd *= 1 + ((player->key_sprint) * 2.25);
		angle_add = 0;
		if (player->key_down && !player->key_up)
			spd = -spd;
		if (player->key_left ^ player->key_right)
		{
			angle_add = 90;
			if (player->key_right)
				angle_add = -angle_add;
			if ((player->key_down ^ player->key_up))
				angle_add /= 2;
			if (spd < 0)
				angle_add = -angle_add;
		}
		move_collision(data, player,
			dcos(player->direction - angle_add) * spd,
			dsin(player->direction - angle_add) * spd);
	}
}

void	turn_player(t_player *player)
{
	double	trn;

	if ((player->key_turn_l ^ player->key_turn_r))
	{
		trn = player->turn_spd;
		if (player->key_turn_l)
			trn = -trn;
		player->direction = angle_limit(player->direction + trn);
	}
}
