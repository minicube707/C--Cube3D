/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmotte <fmotte@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/28 12:57:20 by cpollock          #+#    #+#             */
/*   Updated: 2025/12/13 15:54:17 by fmotte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static double	get_turn_input(t_game *data, t_player *player);

void	init_player(t_player *player)
{
	player->fov = 60;
	player->key_up = false;
	player->key_down = false;
	player->key_left = false;
	player->key_right = false;
	player->key_turn_l = false;
	player->key_turn_r = false;
	player->key_sprint = false;
	player->key_space_pressed = false;
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
		move_collision(data, player, dcos(player->direction - angle_add) * spd,
			dsin(player->direction - angle_add) * spd);
	}
}

void	turn_player(t_game *data, t_player *player)
{
	double	trn;
	double	trn_input;

	trn_input = get_turn_input(data, player);
	if (trn_input != 0)
	{
		trn = (player->turn_spd) * trn_input;
		player->direction = angle_limit(player->direction + trn);
	}
}

static double	get_turn_input(t_game *data, t_player *player)
{
	int		mouse_x;
	int		mouse_y;
	double	mouse_trn;
	double	dead_zone;

	if ((player->key_turn_l ^ player->key_turn_r))
		return (((player->key_turn_r) * 2) - 1);
	mlx_mouse_get_pos(data->mlx, data->win, &mouse_x, &mouse_y);
	if (mouse_x >= 0 && mouse_x <= W_WIDTH && mouse_y >= 0
		&& mouse_y <= W_HEIGHT)
	{
		mouse_trn = mouse_x - (W_WIDTH / 2);
		dead_zone = W_WIDTH * 0.05;
		if (fabs(mouse_trn) > dead_zone)
			return (mouse_trn / (W_WIDTH / 2 - dead_zone));
	}
	return (0);
}
