/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_minimap.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpollock <cpollock@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/05 12:36:23 by cpollock          #+#    #+#             */
/*   Updated: 2025/12/05 12:36:33 by cpollock         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static void	minimap_walls(t_game *data, int unit_len, int map_x, int map_y);
static void	minimap_player(t_game *data, int unit_len, int map_x, int map_y);

void	draw_minimap(t_game *data)
{
	int			unit;
	int			map_x;
	int			map_y;

	if (!data->minimap)
		return ;
	unit = 1;
	if (data->map_width >= data->map_height)
		unit = (W_WIDTH / 5) / data->map_width;
	else
		unit = (W_HEIGHT / 4) / data->map_width;
	map_x = 20;
	map_y = 20;
	minimap_walls(data, unit, map_x, map_y);
	minimap_player(data, unit, map_x, map_y);
}

static void	minimap_walls(t_game *data, int unit_len, int map_x, int map_y)
{
	t_rectangle	wall_rect;
	int			i;
	int			j;

	wall_rect.width = unit_len;
	wall_rect.height = wall_rect.width;
	i = 0;
	while ((data->map)[i] != NULL)
	{
		j = 0;
		while ((data->map)[i][j] != '\0')
		{
			wall_rect.x = map_x + (i * wall_rect.width);
			wall_rect.y = map_y + (j * wall_rect.height);
			if ((data->map)[i][j] == '1')
				draw_rectangle(data, wall_rect, 0x101010);
			else if ((data->map)[i][j] == '0')
				draw_rectangle(data, wall_rect, 0xDDDDDD);
			j++;
		}
		i++;
	}
}

static void	minimap_player(t_game *data, int unit_len, int map_x, int map_y)
{
	t_arrow		player_arrow;
	double		player_map_width;

	player_map_width = unit_len * (data->player.box_width / TILE_LEN);
	player_arrow.width = player_map_width * 1.5;
	player_arrow.height = player_map_width * 1.75;
	player_arrow.pos.x = map_x + (data->player.pos.x / TILE_LEN) * unit_len;
	player_arrow.pos.y = map_y + (data->player.pos.y / TILE_LEN) * unit_len;
	player_arrow.angle = deg2rad(data->player.direction);
	draw_arrow(data, player_arrow, 0xCC0000);
}
