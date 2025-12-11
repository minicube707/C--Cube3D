/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_imgs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpollock <cpollock@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 11:22:53 by cpollock          #+#    #+#             */
/*   Updated: 2025/12/11 11:23:03 by cpollock         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static bool	set_imgs(t_game *data, t_img **img, int *frames, char **files);

bool	init_imgs(t_game *data, t_imgtextures *imgs)
{
	char	*northtest[2] = {"./textures/Wall_Nord.xpm", NULL};
	char	*southtest[2] = {"./textures/Wall_Sud.xpm", NULL};
	char	*easttest[2] = {"./textures/Wall_Est.xpm", NULL};
	char	*westtest[2] = {"./textures/Wall_Wouest.xpm", NULL};
	char	*doortest[5] = {"./textures/Wall_Door.xpm", "./textures/Wall_Nord.xpm",
							"./textures/Wall_Door.xpm", "./textures/Wall_Sud.xpm", NULL};

	set_imgs(data, &(imgs->wall_north), &(imgs->frames_north), northtest);
	set_imgs(data, &(imgs->wall_south), &(imgs->frames_south), southtest);
	set_imgs(data, &(imgs->wall_east), &(imgs->frames_east), easttest);
	set_imgs(data, &(imgs->wall_west), &(imgs->frames_west), westtest);
	set_imgs(data, &(imgs->wall_door), &(imgs->frames_door), doortest);
	return (true);
}

static bool	set_imgs(t_game *data, t_img **img, int *frames, char **files)
{
	int	i;

	*frames = 0;
	while (files[*frames] != NULL)
		*frames += 1;
	*img = (t_img *) malloc((*frames) * sizeof(t_img));
	if (*img == NULL)
		return (false);
	i = 0;
	while (i < *frames)
	{
		((*img)[i]).img_width = 64;
		((*img)[i]).img_height = 64;
		((*img)[i]).sprite = mlx_xpm_file_to_image(data->mlx, files[i],
				&(((*img)[i]).img_width), &(((*img)[i]).img_height));
		((*img)[i]).addr = mlx_get_data_addr(((*img)[i]).sprite, &((*img)[i]).bbp,
				&((*img)[i]).line_len, &((*img)[i]).endian);
		i++;
	}
	return (true);
}
