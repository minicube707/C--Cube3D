/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_texture3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmotte <fmotte@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/12 15:52:29 by fmotte            #+#    #+#             */
/*   Updated: 2025/12/12 16:48:05 by fmotte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
