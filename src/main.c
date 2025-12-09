/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmotte <fmotte@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/28 11:12:30 by cpollock          #+#    #+#             */
/*   Updated: 2025/12/09 15:48:23 by fmotte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static bool	init_game(t_game *data);

int	main(int argc, char **argv)
{
	t_game	data;

	if (argc != 2)
	{
		printf("Error\nWrong number of argument\n");
		return (1);
	}
	if (parsing(argv[1], &data))
		return (0);
	if (!init_game(&data))
		return (1);
	init_player(&data.player);
	mlx_hook(data.win, DestroyNotify, StructureNotifyMask, &kill_game, &data);
	mlx_hook(data.win, KeyPress, KeyPressMask, &key_press, &data);
	mlx_hook(data.win, KeyRelease, KeyReleaseMask, &key_release, &data);
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
	data->minimap = false;
	gettimeofday(&data->time_frame, NULL);
	return (true);
}
