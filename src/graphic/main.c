/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmotte <fmotte@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/28 11:12:30 by cpollock          #+#    #+#             */
/*   Updated: 2025/12/12 17:33:49 by fmotte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	print_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i] != NULL)
	{
		printf("%s", tab[i]);
		printf("\n");
		i++;
	}
}

void	print_texture(t_game *data)
{
	print_tab(data->texture.texture_north);
	print_tab(data->texture.texture_south);
	print_tab(data->texture.texture_east);
	print_tab(data->texture.texture_west);
	if (data->texture.texture_door != NULL)
		print_tab(data->texture.texture_door);
}

int	main(int argc, char **argv)
{
	t_game	data;

	if (argc != 2)
		return (ft_perror("Wrong number of arguments\n"));
	if (parsing(argv[1], &data))
		return (1);
	if (!init_game(&data))
		return (kill_game(&data), 1);
	print_texture(&data);
	init_player(&data.player);
	mlx_hook(data.win, DestroyNotify, StructureNotifyMask, &close_game, &data);
	mlx_hook(data.win, KeyPress, KeyPressMask, &key_press, &data);
	mlx_hook(data.win, KeyRelease, KeyReleaseMask, &key_release, &data);
	mlx_loop_hook(data.mlx, loop_event, &data);
	mlx_loop(data.mlx);
	return (0);
}
