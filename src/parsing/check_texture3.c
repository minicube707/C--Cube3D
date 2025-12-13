/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_texture3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmotte <fmotte@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/12 15:52:29 by fmotte            #+#    #+#             */
/*   Updated: 2025/12/13 14:10:32 by fmotte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	texture_copy_info_utils(t_game *data, char **tmp_tab, int i)
{
	if (i == 0)
		data->texture.texture_north = tmp_tab;
	else if (i == 1)
		data->texture.texture_south = tmp_tab;
	else if (i == 2)
		data->texture.texture_east = tmp_tab;
	else if (i == 3)
		data->texture.texture_west = tmp_tab;
	else if (i == 3)
		data->texture.texture_west = tmp_tab;
	else if (i == 4)
		data->texture.texture_door = tmp_tab;
	return (0);
}

int	texture_copy_info(t_game *data, char *tmp, int i, int mode_single)
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
	else if (i == 4)
		tmp_tab = data->texture.texture_door;
	if (tmp_tab != NULL && mode_single)
	{
		free(tmp);
		return (ft_perror("Texture duplicate\n"));
	}
	tmp_tab = ft_realloc(tmp_tab, tmp);
	if (tmp_tab == NULL)
	{
		free(tmp);
		return (ft_perror("Probleme allocation dynamique\n"));
	}
	return (texture_copy_info_utils(data, tmp_tab, i));
}
