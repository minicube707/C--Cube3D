/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_texture2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmotte <fmotte@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 14:48:29 by fmotte            #+#    #+#             */
/*   Updated: 2025/12/11 18:10:34 by fmotte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	clear_texture(t_game *data)
{
	tab_char_clear(data->texture.texture_north);
	tab_char_clear(data->texture.texture_south);
	tab_char_clear(data->texture.texture_east);
	tab_char_clear(data->texture.texture_west);
}

int	texture_copy_info(t_game *data, char *tmp, int i)
{
	char	**tmp_tab;

	tmp_tab = NULL;
	if (i == 0)
		tmp_tab = data->texture.texture_north;
	else if (i == 1)
		tmp_tab = data->texture.texture_south;
	else if (i == 2)
		tmp_tab = data->texture.texture_east;
	else if (i == 3)
		tmp_tab = data->texture.texture_west;
	tmp_tab = ft_realloc(tmp_tab, tmp);
	if (tmp_tab == NULL)
		return (1);
	if (i == 0)
		data->texture.texture_north = tmp_tab;
	else if (i == 1)
		data->texture.texture_south = tmp_tab;
	else if (i == 2)
		data->texture.texture_east = tmp_tab;
	else if (i == 3)
		data->texture.texture_west = tmp_tab;
	return (0);
}

static int	manage_data_utils(t_game *data, char *string, int i)
{
	char	*tmp;
	char	*tmp2;

	tmp = skip_white_space(string);
	free(string);
	if (tmp == NULL)
		return (ft_perror("Probleme allocation dynamique\n"));
	tmp2 = ft_substr(tmp, 0, ft_strlen(tmp) - 1);
	free(tmp);
	if (tmp2 == NULL)
		return (ft_perror("Probleme allocation dynamique\n"));
	if (!check_extension(tmp2, ".xpm"))
	{
		printf("Error\nWrong extention. Can't open file %s\n", tmp2);
		free(tmp2);
		return (1);
	}
	if (texture_copy_info(data, tmp2, i))
	{
		free(tmp2);
		return (ft_perror("Probleme allocation dynamique\n"));
	}
	return (0);
}

static int	manage_data(t_game *data, int fd, int i)
{
	char	*string;

	string = "";
	while (string != NULL)
	{
		string = get_next_line(fd);
		if (string != NULL)
		{
			if (!ft_is_visible(string))
			{
				free(string);
				continue ;
			}
			if (manage_data_utils(data, string, i))
				return (1);
		}
	}
	return (0);
}

int	check_texture2(t_game *data, char *name_file, int i)
{
	int	fd;
	int	res;

	fd = open_map(name_file);
	free(name_file);
	if (fd == -1)
		return (1);
	res = manage_data(data, fd, i);
	close(fd);
	if (res)
		return (1);
	return (0);
}
