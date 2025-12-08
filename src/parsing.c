/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmotte <fmotte@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 14:58:28 by fmotte            #+#    #+#             */
/*   Updated: 2025/12/08 17:49:37 by fmotte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_data(char **tab_map, char **tab_tex, char **tab_col, t_game *data)
{
	if (tab_map == NULL || tab_tex == NULL || tab_col == NULL)
	{
		printf("KO Instruction\n");
		return (1);
	}
	if (check_map(tab_map))
	{
		printf("KO Map\n");
		return (1);
	}
	if (check_colour(tab_col, data))
	{
		printf("KO Colour\n");
		return (1);
	}
	if (chec_texture(tab_tex))
	{
		printf("KO Texture\n");
		return (1);
	}
	return (0);
}

int	open_map(char *name_map)
{
	int		fd;
	char	*path;

	path = ft_strjoin("maps/good/", name_map);
	if (path == NULL)
	{
		printf("Error: fail malloc\n");
		return (-1);
	}
	fd = open(path, O_RDONLY);
	free(path);
	if (fd > 2)
		return (fd);
	path = ft_strjoin("maps/bad/", name_map);
	if (path == NULL)
	{
		printf("Error: fail malloc\n");
		return (-1);
	}
	fd = open(path, O_RDONLY);
	free(path);
	if (fd > 2)
		return (fd);
	printf("Error 404: %s file not found\n", name_map);
	return (-1);
}

char **ft_transpose(char **tab_map)
{
	char **new_tab;
	int height;
	int width;
	int i;
	int j;
	
	height = lenght_tab(tab_map);
	width = get_width_map(tab_map);
	
	new_tab = malloc(sizeof(char *) * (width + 1));
	if (new_tab == NULL)
	{
		tab_char_clear(tab_map);
		return (NULL);
	}
	i = 0;
	while (i < width)
	{
		j = 0;
		new_tab[i] = malloc(sizeof(char) * height);
		if (new_tab[i] == NULL)
		{
			tab_char_clear(new_tab);
			return (NULL);
		}
 		while (j <= height -2)
		{
			
			if (ft_strlen(tab_map[j]) > i && tab_map[j][i] != '\n')
				new_tab[i][j] = tab_map[j][i];
			else
				new_tab[i][j] = '0';
			j++;
		}
		new_tab[i][j] = '\0';
		i++;
	}
	new_tab[i] = NULL;
	return (new_tab);
}

int	manage_data(int fd, t_game *data)
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
		if (string != NULL && lenght_tab(tab_col) == 3
			&& lenght_tab(tab_tex) == 5)
			tab_map = ft_realloc(tab_map, string);
		else if (string != NULL)
		{
			if (fill_information(string, &tab_tex, &tab_col))
				return (clear_parsing(tab_map, tab_tex, tab_col));
		}
	}
	if (check_data(tab_map, tab_tex, tab_col, data))
		return (clear_parsing(tab_map, tab_tex, tab_col));
		
	int i;
	i = 0;
	printf("TAB\n");
	while (tab_map[i] != NULL)
	{
		printf("%s", tab_map[i]);
		i++;
	}
	
	data->map = ft_transpose(tab_map);
	clear_parsing(tab_map, tab_tex, tab_col);

	i = 0;
	printf("DATA\n");
	while (data->map[i] != NULL)
	{
		printf("%s\n", data->map[i]);
		i++;
	}
	return (0);
}

int	parsing(char *name_map, t_game *data)
{
	int	fd;

	if (!check_extension(name_map, ".cub"))
		return (1);
	fd = open_map(name_map);
	if (fd == -1)
		return (1);
	if (manage_data(fd, data))
		return (1);
	return (0);
}
