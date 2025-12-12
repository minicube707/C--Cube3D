/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_texture2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmotte <fmotte@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 14:48:29 by fmotte            #+#    #+#             */
/*   Updated: 2025/12/12 16:57:10 by fmotte           ###   ########.fr       */
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

static int	manage_data_utils_add_path(t_game *data, char *string, char *path, int i)
{
	char *tmp;
	char *tmp2;
	
	if (path[ft_strlen(path)] != '/' && string[0] != '/')
	{
		tmp = ft_strjoin(path, "/");
		if (tmp == NULL)
		{
			free(string);
			return (ft_perror("Probleme allocation dynamique\n"));
		}
		tmp2 = ft_strjoin(tmp, string);
		free(tmp);
	}
	else
		tmp2 = ft_strjoin(path, string);
	free(string);
	if (tmp2 == NULL)
		return (ft_perror("Probleme allocation dynamique\n"));
	if (texture_copy_info(data, tmp2, i))
	{
		free(tmp2);
		return (ft_perror("Probleme allocation dynamique\n"));
	}
	return (0);
}

static int	manage_data_utils(t_game *data, char *string, char *path, int i)
{
	char	*tmp;
	char	*img;

	tmp = skip_white_space(string);
	free(string);
	if (tmp == NULL)
		return (ft_perror("Probleme allocation dynamique\n"));
	img = ft_substr(tmp, 0, ft_strlen(tmp) - 1);
	free(tmp);
	if (img == NULL)
		return (ft_perror("Probleme allocation dynamique\n"));
	if (!check_extension(img, ".xpm"))
	{
		printf("Error\nWrong extention. Can't open file %s\n", img);
		free(img);
		return (1);
	}
	return (manage_data_utils_add_path(data, img, path, i));
}

static int	manage_data(t_game *data, int fd, char *path, int i)
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
			if (manage_data_utils(data, string, path, i))
			{
				free(path);
				return (1);
			}
		}
	}
	free(path);
	return (0);
}

int	check_texture2(t_game *data, char *path_utils, char *path, int i)
{
	int	fd;
	int	res;

	fd = open_map(path_utils);
	free(path_utils);
	if (fd == -1)
		return (1);
	res = manage_data(data, fd, path, i);
	close(fd);
	if (res)
		return (1);
	return (0);
}
