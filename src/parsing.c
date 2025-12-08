/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmotte <fmotte@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 14:58:28 by fmotte            #+#    #+#             */
/*   Updated: 2025/12/08 15:13:34 by fmotte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_data(char **tab_map, char **tab_tex, char **tab_col)
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
	if (check_colour(tab_col))
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

int	manage_data(int fd)
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
	if (check_data(tab_map, tab_tex, tab_col))
		return (clear_parsing(tab_map, tab_tex, tab_col));
	clear_parsing(tab_map, tab_tex, tab_col);
	return (0);
}

int	parsing(char *name_map)
{
	int	fd;

	if (!check_extension(name_map, ".cub"))
		return (1);
	fd = open_map(name_map);
	if (fd == -1)
		return (1);
	if (manage_data(fd))
		return (1);
	return (0);
}
