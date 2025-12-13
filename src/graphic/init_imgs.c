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
static bool	wipeout_imgs(t_game *data, t_img **img, int i);
static void	img_error(char *image_name);

bool	init_imgs(t_game *data, t_imgtextures *imgs, t_texture *texts)
{
	char	**tx_files;

	tx_files = texts->texture_north;
	if (!set_imgs(data, &(imgs->wall_north), &(imgs->frames_north), tx_files))
		return (false);
	tx_files = texts->texture_south;
	if (!set_imgs(data, &(imgs->wall_south), &(imgs->frames_south), tx_files))
		return (false);
	tx_files = texts->texture_east;
	if (!set_imgs(data, &(imgs->wall_east), &(imgs->frames_east), tx_files))
		return (false);
	tx_files = texts->texture_west;
	if (!set_imgs(data, &(imgs->wall_west), &(imgs->frames_west), tx_files))
		return (false);
	if (texts->texture_door != NULL)
		tx_files = texts->texture_door;
	if (!set_imgs(data, &(imgs->wall_door), &(imgs->frames_door), tx_files))
		return (false);
	return (true);
}

static bool	set_imgs(t_game *data, t_img **img, int *frames, char **files)
{
	int	i;

	*frames = 0;
	while (files != NULL && files[*frames] != NULL)
		*frames += 1;
	if (*frames == 0)
		return (printf("Error\nMissing texture files\n"), false);
	*img = (t_img *) malloc((*frames) * sizeof(t_img));
	if (*img == NULL)
		return (printf("Error\nImage array malloc error\n"), false);
	i = 0;
	while (i < *frames)
	{
		((*img)[i]).img_width = 64;
		((*img)[i]).img_height = 64;
		((*img)[i]).sprite = mlx_xpm_file_to_image(data->mlx, files[i],
				&(((*img)[i]).img_width), &(((*img)[i]).img_height));
		if (((*img)[i]).sprite == NULL)
			return (img_error(files[i]), wipeout_imgs(data, img, i));
		((*img)[i]).addr = mlx_get_data_addr(((*img)[i]).sprite,
				&((*img)[i]).bbp, &((*img)[i]).line_len, &((*img)[i]).endian);
		i++;
	}
	return (true);
}

static bool	wipeout_imgs(t_game *data, t_img **img, int i)
{
	i -= 1;
	while (i >= 0)
		mlx_destroy_image(data->mlx, (*img)[i--].sprite);
	free(*img);
	*img = NULL;
	return (false);
}

static void	img_error(char *img_name)
{
	printf("Error\n");
	printf("Could not open %s\n", img_name);
}
