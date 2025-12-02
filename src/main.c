/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpollock <cpollock@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/28 11:12:30 by cpollock          #+#    #+#             */
/*   Updated: 2025/11/28 11:12:41 by cpollock         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static bool	init_game(t_game *data);
static int	kill_game(t_game *data);
static int	esc_game(int key, t_game *data);

int	main(int arg_c, char *arg_s[])
{
	t_game	data;

	(void) arg_c;
	(void) arg_s;
	if (!init_game(&data))
		return (1);
	init_player(&data.player, W_WIDTH / 2, W_HEIGHT / 2, 270);
	mlx_hook(data.win, DestroyNotify, StructureNotifyMask, &kill_game, &data);
	mlx_hook(data.win, KeyRelease, KeyReleaseMask, &esc_game, &data);
	mlx_hook(data.win, KeyPress, KeyPressMask, &key_press, &data.player);
	mlx_hook(data.win, KeyRelease, KeyReleaseMask, &key_release, &data.player);
	mlx_loop_hook(data.mlx, loop_event, &data);
	mlx_loop(data.mlx);
	return (0);
}

static bool	init_game(t_game *data)
{
	data->mlx = mlx_init();
	if (data->mlx == NULL)
		return (false);
	data->img = mlx_new_image(data->mlx, W_WIDTH, W_HEIGHT);
	if (data->img == NULL)
		return (free(data->mlx), false);
	data->addr = mlx_get_data_addr(data->img, &data->bbp, &data->line_len,
			&data->endian);
	data->win = mlx_new_window(data->mlx, W_WIDTH, W_HEIGHT, GAMENAME);
	if (data->win == NULL)
		return (free(data->mlx), false);
	if (!init_map(data))
		return (free(data->mlx), false);
	return (true);
}

static int	kill_game(t_game *data)
{
	mlx_destroy_window(data->mlx, data->win);
	mlx_destroy_image(data->mlx, data->img);
	mlx_destroy_display(data->mlx);
	free(data->mlx);
	wipeout_map(data);
	exit(0);
	return (0);
}

static int	esc_game(int key, t_game *data)
{
	if (key == ESC)
		kill_game(data);
	return (0);
}
