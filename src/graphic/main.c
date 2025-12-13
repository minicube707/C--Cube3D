/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmotte <fmotte@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/28 11:12:30 by cpollock          #+#    #+#             */
/*   Updated: 2025/12/13 13:55:43 by fmotte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int argc, char **argv)
{
	t_game	data;

	if (argc != 2)
		return (ft_perror("Wrong number of arguments\n"));
	if (parsing(argv[1], &data))
		return (1);
	if (!init_game(&data))
		return (kill_game(&data), 1);
	init_player(&data.player);
	mlx_hook(data.win, DestroyNotify, StructureNotifyMask, &close_game, &data);
	mlx_hook(data.win, KeyPress, KeyPressMask, &key_press, &data);
	mlx_hook(data.win, KeyRelease, KeyReleaseMask, &key_release, &data);
	mlx_loop_hook(data.mlx, loop_event, &data);
	mlx_loop(data.mlx);
	return (0);
}
