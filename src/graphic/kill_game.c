/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kill_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmotte <fmotte@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 13:45:42 by cpollock          #+#    #+#             */
/*   Updated: 2025/12/11 18:48:13 by fmotte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	kill_images(t_game *data, t_img **img, int frames);

int	close_game(t_game *data)
{
	kill_game(data);
	exit(0);
	return (0);
}

void	kill_game(t_game *data)
{
	t_imgtextures	*data_imgs;

	if (data->win != NULL)
		mlx_destroy_window(data->mlx, data->win);
	if (data->img != NULL)
		mlx_destroy_image(data->mlx, data->img);
	data_imgs = &(data->wall_imgs);
	kill_images(data, &(data_imgs->wall_north), data_imgs->frames_north);
	kill_images(data, &(data_imgs->wall_south), data_imgs->frames_south);
	kill_images(data, &(data_imgs->wall_east), data_imgs->frames_east);
	kill_images(data, &(data_imgs->wall_west), data_imgs->frames_west);
	kill_images(data, &(data_imgs->wall_door), data_imgs->frames_door);
	if (data->mlx != NULL)
	{
		mlx_destroy_display(data->mlx);
		free(data->mlx);
	}
	tab_char_clear(data->map);
	clear_texture(data);
}

static void	kill_images(t_game *data, t_img **img, int frames)
{
	int	i;

	if (*img == NULL)
		return ;
	i = 0;
	while (i < frames)
		mlx_destroy_image(data->mlx, (*img)[i++].sprite);
	free(*img);
}
