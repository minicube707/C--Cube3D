/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmotte <fmotte@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 14:58:28 by fmotte            #+#    #+#             */
/*   Updated: 2025/12/11 18:31:02 by fmotte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_data(char **tab_map, char **tab_tex, char **tab_col, t_game *data)
{
	if (tab_map == NULL || tab_tex == NULL || tab_col == NULL)
		return (ft_perror("KO Instruction\n"));
	if (check_map(tab_map))
		return (ft_perror("KO Map\n"));
	if (check_colour(tab_col, data))
		return (ft_perror("KO Colour\n"));
	if (check_texture(tab_tex, data))
		return (ft_perror("KO Texture\n"));
	return (0);
}

int	open_map(char *name_map)
{
	int	fd;

	fd = open(name_map, O_RDONLY);
	if (fd > 2)
		return (fd);
	printf("Error\n404 %s file not found\n", name_map);
	return (-1);
}

static int	manage_data_utils(char **tab_map, char **tab_tex, char **tab_col,
		t_game *data)
{
	t_coord	coord;

	if (check_data(tab_map, tab_tex, tab_col, data))
		return (clear_parsing(tab_map, tab_tex, tab_col));
	data->map = ft_transpose(tab_map);
	if (data->map == NULL)
	{
		clear_parsing(tab_map, tab_tex, tab_col);
		clear_texture(data);
		return (ft_perror("Probleme allocation dynamique\n"));
	}
	coord = get_pos_player(tab_map);
	data->map_height = lenght_tab(tab_map);
	data->map_width = get_width_map(tab_map);
	clear_parsing(tab_map, tab_tex, tab_col);
	data->player.pos.x = (double)(coord.x * TILE_LEN) + (TILE_LEN / 2);
	data->player.pos.y = (double)(coord.y * TILE_LEN) + (TILE_LEN / 2);
	data->player.direction = (double)get_ori_player(data->map) * 90;
	return (0);
}

static int	manage_data(int fd, t_game *data)
{
	char	*string;
	char	**tab_map;
	char	**tab_tex;
	char	**tab_col;

	tab_map = NULL;
	tab_tex = NULL;
	tab_col = NULL;
	string = "";
	while (string != NULL)
	{
		string = get_next_line(fd);
		if (manage_data_loop(&tab_map, &tab_tex, &tab_col, string))
			return (ft_perror("Probleme allocation dynamique\n"));
	}
	return (manage_data_utils(tab_map, tab_tex, tab_col, data));
}

int	parsing(char *name_map, t_game *data)
{
	int	fd;
	int	res;

	if (!check_extension(name_map, ".cub"))
	{
		printf("Error\nWrong extention. Can't open file %s\n", name_map);
		return (1);
	}
	fd = open_map(name_map);
	if (fd == -1)
		return (1);
	res = manage_data(fd, data);
	close(fd);
	if (res)
		return (1);
	return (0);
}
