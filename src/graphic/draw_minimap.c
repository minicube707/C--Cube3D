/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_minimap.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmotte <fmotte@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/05 12:36:23 by cpollock          #+#    #+#             */
/*   Updated: 2025/12/13 14:12:37 by fmotte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	minimap_walls(t_game *data, int unit_len, int map_x, int map_y);
static int	map_wall_col(char map_c);
static void	minimap_player(t_game *data, int unit_len, int map_x, int map_y);
static int	count_empty_rows(t_game *data);

void	draw_minimap(t_game *data)
{
	int	unit;
	int	map_x;
	int	map_y;
	int	skip_rows;

	if (!data->minimap)
		return ;
	unit = 1;
	skip_rows = count_empty_rows(data);
	if ((data->map_width - 1) >= (data->map_height - skip_rows - 1))
		unit = (W_WIDTH / 5) / (data->map_width - 1);
	else
		unit = (W_HEIGHT / 4) / (data->map_height - skip_rows - 1);
	if (unit < 2)
		unit = 2;
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
	int			skip_rows;

	wall_rect.width = unit_len;
	wall_rect.height = wall_rect.width;
	i = 0;
	skip_rows = count_empty_rows(data);
	while (i < data->map_width - 1)
	{
		j = skip_rows;
		while (j < data->map_height - 1)
		{
			wall_rect.x = map_x + (i * wall_rect.width);
			wall_rect.y = map_y + ((j - skip_rows) * wall_rect.height);
			if ((data->map)[i][j] != ' ')
				draw_rectangle(data, wall_rect,
					map_wall_col((data->map)[i][j]));
			j++;
		}
		i++;
	}
}

static int	map_wall_col(char map_c)
{
	if (map_c == '1')
		return (0x101010);
	if (map_c == 'D')
		return (0x009000);
	if (map_c == 'O')
		return (0xB8B8B8);
	return (0xDDDDDD);
}

static void	minimap_player(t_game *data, int unit_len, int map_x, int map_y)
{
	t_arrow	player_arrow;
	double	player_map_width;

	player_map_width = unit_len * (data->player.box_width / TILE_LEN);
	player_arrow.width = player_map_width * 1.5;
	player_arrow.height = player_map_width * 1.75;
	player_arrow.pos.x = map_x + (data->player.pos.x / TILE_LEN) * unit_len;
	player_arrow.pos.y = map_y + (data->player.pos.y / TILE_LEN) * unit_len;
	player_arrow.pos.y -= count_empty_rows(data) * unit_len;
	player_arrow.angle = deg2rad(data->player.direction);
	draw_arrow(data, player_arrow, 0xCC0000);
}

static int	count_empty_rows(t_game *data)
{
	int	i;
	int	j;

	j = 0;
	while (j < data->map_height)
	{
		i = 0;
		while (i < data->map_width - 1)
		{
			if ((data->map)[i][j] != '0' && (data->map)[i][j] != ' ')
				return (j);
			i++;
		}
		j++;
	}
	return (j);
}
