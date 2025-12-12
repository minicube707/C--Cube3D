/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpollock <cpollock@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/12 11:31:39 by cpollock          #+#    #+#             */
/*   Updated: 2025/12/12 11:31:51 by cpollock         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	game_set_null_default(t_game *data);
static bool	set_door_state(t_game *data);
static void	init_error(char *str);

bool	init_game(t_game *data)
{
	game_set_null_default(data);
	data->mlx = mlx_init();
	if (data->mlx == NULL)
		return (init_error("Mlx malloc error"), false);
	if (gettimeofday(&data->time_fps, NULL) == -1
		|| gettimeofday(&data->time_anim, NULL) == -1)
		return (init_error("gettimeofday error"), false);
	if (!set_door_state(data))
		return (init_error("Int array malloc error"), false);
	data->img = mlx_new_image(data->mlx, W_WIDTH, W_HEIGHT);
	if (!init_imgs(data, &(data->wall_imgs), &(data->texture)))
		return (false);
	if (data->img == NULL)
		return (init_error("Image creation error"), false);
	data->addr = mlx_get_data_addr(data->img, &data->bbp, &data->line_len,
			&data->endian);
	data->win = mlx_new_window(data->mlx, W_WIDTH, W_HEIGHT, GAMENAME);
	if (data->win == NULL)
		return (init_error("Window creation error"), false);
	return (true);
}

static void	game_set_null_default(t_game *data)
{
	data->mlx = NULL;
	data->img = NULL;
	data->win = NULL;
	data->wall_imgs.wall_north = NULL;
	data->wall_imgs.wall_south = NULL;
	data->wall_imgs.wall_east = NULL;
	data->wall_imgs.wall_west = NULL;
	data->wall_imgs.wall_door = NULL;
	data->door_state = NULL;
	data->minimap = false;
	data->ms_fps = 0;
	data->ms_anim = 0;
}

static bool	set_door_state(t_game *data)
{
	int	i;
	int	j;

	data->door_state = (int **) malloc(data->map_width * sizeof(int *));
	if (data->door_state == NULL)
		return (false);
	i = 0;
	while (i < data->map_width)
	{
		(data->door_state)[i] = (int *) malloc(data->map_height * sizeof(int));
		if ((data->door_state)[i] == NULL)
			return (false);
		j = 0;
		while (j < data->map_height)
			(data->door_state)[i][j++] = 100;
		i++;
	}
	return (true);
}

static void	init_error(char *str)
{
	printf("Error\n");
	printf("%s\n", str);
}
