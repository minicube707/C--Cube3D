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
	player->plane_dist = 20;
	player->key_up = false;
	player->key_down = false;
	player->key_left = false;
	player->key_right = false;
	player->key_turn_l = false;
	player->key_turn_r = false;
	player->box_width = 50;
	player->walk_spd = 0.5;
	player->turn_spd = 0.5;
}

int	key_press(int key, t_player *player)
{
	if (key == W)
		player->key_up = true;
	if (key == S)
		player->key_down = true;
	if (key == A)
		player->key_left = true;
	if (key == D)
		player->key_right = true;
	if (key == LEFT)
		player->key_turn_l = true;
	if (key == RIGHT)
		player->key_turn_r = true;
	return (0);
}

int	key_release(int key, t_player *player)
{
	if (key == W)
		player->key_up = false;
	if (key == S)
		player->key_down = false;
	if (key == A)
		player->key_left = false;
	if (key == D)
		player->key_right = false;
	if (key == LEFT)
		player->key_turn_l = false;
	if (key == RIGHT)
		player->key_turn_r = false;
	return (0);
}

void	move_player(t_player *player)
{
	double	spd;
	double	angle_add;
	
	if ((player->key_up ^ player->key_down)
		|| (player->key_left ^ player->key_right))
	{
		spd = player->walk_spd;
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
		player->pos.x += dcos(player->direction - angle_add) * spd;
		player->pos.y += dsin(player->direction - angle_add) * spd;
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
		player->direction = fmod(player->direction + trn, 360);
	}
}
