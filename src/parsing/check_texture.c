/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_texture.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmotte <fmotte@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/05 16:30:59 by fmotte            #+#    #+#             */
/*   Updated: 2025/12/11 17:49:18 by fmotte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	init_texture(t_game *data)
{
	data->texture.texture_north = NULL;
	data->texture.texture_south = NULL;
	data->texture.texture_east = NULL;
	data->texture.texture_west = NULL;
}

static int	check_texture_path_utils(t_game *data, char *tmp, int i)
{
	char	*path;
	int		fd;
	int		res;

	path = malloc(sizeof(char) * (ft_strlen(tmp) + 11));
	if (path == NULL)
		return (ft_perror("Probleme allocation dynamique\n"));
	path = ft_bzero(path, ft_strlen(tmp) + 11);
	ft_strncpy(path, tmp, ft_strlen(tmp));
	ft_strlcat(path, "/utils.txt", ft_strlen(path) + 11);
	fd = open(path, O_RDONLY);
	free(tmp);
	if (fd == -1)
	{
		printf("Error\nWrong extension. Can't open file %s\n", path);
		ft_perror("404 /utils.txt file not found\n");
		free(path);
		return (1);
	}
	res = check_texture2(data, path, i);
	close(fd);
	return (res);
}

static int	check_texture_path(t_game *data, char *string, int i)
{
	char	*tmp;
	char	*tmp2;

	tmp = skip_white_space(string);
	if (tmp == NULL)
		return (ft_perror("Probleme allocation dynamique\n"));
	tmp2 = ft_substr(tmp, 0, ft_strlen(tmp) - 1);
	free(tmp);
	if (tmp2 == NULL)
		return (ft_perror("Probleme allocation dynamique\n"));
	if (check_extension(tmp2, ".xpm"))
	{
		if (texture_copy_info(data, tmp2, i))
			return (ft_perror("Probleme allocation dynamique\n"));
		return (0);
	}
	return (check_texture_path_utils(data, tmp2, i));
}

static int	check_texture_utils(t_game *data, char *tab_string, char *string,
		int i)
{
	char	*sub_string;

	sub_string = ft_substr(tab_string, i * 2, 2);
	if (sub_string == NULL)
		return (1);
	if (ft_strncmp(string, sub_string, 2) == 0)
	{
		if (check_texture_path(data, string + 2, i))
		{
			free(sub_string);
			return (1);
		}
	}
	free(sub_string);
	return (0);
}

int	check_texture(char **tab_tex, t_game *data)
{
	char	*tab_string;
	int		i;
	int		j;

	tab_string = "NOSOEAWE";
	init_texture(data);
	i = 0;
	while (i < 4)
	{
		j = 0;
		while (j < 4)
		{
			if (check_texture_utils(data, tab_string, tab_tex[j], i))
			{
				clear_texture(data);
				return (1);
			}
			j++;
		}
		i++;
	}
	return (0);
}
