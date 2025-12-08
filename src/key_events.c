/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_events.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpollock <cpollock@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 14:21:55 by cpollock          #+#    #+#             */
/*   Updated: 2025/12/04 14:22:37 by cpollock         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	key_press(int key, t_game *data)
{
	if (key == W)
		data->player.key_up = true;
	if (key == S)
		data->player.key_down = true;
	if (key == A)
		data->player.key_left = true;
	if (key == D)
		data->player.key_right = true;
	if (key == LEFT)
		data->player.key_turn_l = true;
	if (key == RIGHT)
		data->player.key_turn_r = true;
	if (key == LSHIFT)
		data->player.key_sprint = true;
	if (key == M)
		data->minimap = !data->minimap;
	return (0);
}

int	key_release(int key, t_game *data)
{
	if (key == W)
		data->player.key_up = false;
	if (key == S)
		data->player.key_down = false;
	if (key == A)
		data->player.key_left = false;
	if (key == D)
		data->player.key_right = false;
	if (key == LEFT)
		data->player.key_turn_l = false;
	if (key == RIGHT)
		data->player.key_turn_r = false;
	if (key == LSHIFT)
		data->player.key_sprint = false;
	if (key == ESC)
		kill_game(data);
	return (0);
}

int	kill_game(t_game *data)
{
	mlx_destroy_window(data->mlx, data->win);
	mlx_destroy_image(data->mlx, data->img);
	mlx_destroy_display(data->mlx);
	free(data->mlx);
	wipeout_map(data);
	exit(0);
	return (0);
}
