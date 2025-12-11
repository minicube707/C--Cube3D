/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmotte <fmotte@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/28 11:12:30 by cpollock          #+#    #+#             */
/*   Updated: 2025/12/11 18:05:27 by fmotte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static bool	init_game(t_game *data);

void	print_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i] != NULL)
	{
		printf("%s",tab[i]);
		printf("\n");
		i++;
	}
}

void print_texture(t_game *data)
{
	print_tab(data->texture.texture_north);
	print_tab(data->texture.texture_south);
	print_tab(data->texture.texture_east);
	print_tab(data->texture.texture_west);
}
int	main(int argc, char **argv)
{
	t_game	data;

	if (argc != 2)
		return (ft_perror("Wrong number of argument\n"));
	if (parsing(argv[1], &data))
		return (1);
	if (!init_game(&data))
		return (1);
	print_texture(&data);
	kill_game(&data);
	return(0);
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
