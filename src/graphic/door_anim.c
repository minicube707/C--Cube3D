/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door_anim.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpollock <cpollock@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/12 15:21:46 by cpollock          #+#    #+#             */
/*   Updated: 2025/12/12 15:22:00 by cpollock         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	door_anim(t_game *data)
{
	int		i;
	int		j;
	char	map_tile;
	int		door_spd;

	door_spd = 5;
	i = 0;
	while (i < data->map_width)
	{
		j = 0;
		while (j < data->map_height)
		{
			map_tile = (data->map)[i][j];
			if (map_tile == 'D' && (data->door_state)[i][j] < 100)
				(data->door_state)[i][j] += door_spd;
			if (map_tile == 'O' && (data->door_state)[i][j] > 0)
				(data->door_state)[i][j] -= door_spd;
			j++;
		}
		i++;
	}
}

int	door_img_x_add(t_game *data, t_raydata ray, t_img img)
{
	t_coord	map_coord;
	char	map_tile;
	int		door_add;

	map_tile = vect_get_tile(data, ray.vect);
	if (map_tile == 'D' || map_tile == 'O')
	{
		vect_to_mapcoord(ray.vect, &map_coord);
		door_add = 100 - ((data->door_state)[map_coord.x][map_coord.y]);
		door_add = (img.img_width * door_add) / 100;
		if (ray.wall_side == 1 || ray.wall_side == 3)
			door_add = -door_add;
		return (door_add);
	}
	return (0);
}
