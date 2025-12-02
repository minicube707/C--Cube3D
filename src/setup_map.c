/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpollock <cpollock@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 12:33:41 by cpollock          #+#    #+#             */
/*   Updated: 2025/12/02 12:33:52 by cpollock         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"
#include <string.h>

bool	init_map(t_game *data)
{
	int	i;

	data->map_width = 19;
	data->map_height = 10;
	data->map = (char **) malloc((data->map_width + 1) * sizeof(char *));
	if (data->map == NULL)
		return (false);
	i = 0;
	while (i < data->map_width)
	{
		(data->map)[i] = (char *) malloc((data->map_height + 1) * sizeof(char));
		if ((data->map)[i++] == NULL)
			return (wipeout_map(data), false);
	}
	(data->map)[i] = NULL;
	return (true);
}

void	wipeout_map(t_game *data)
{
	int	i;

	if (data->map != NULL)
	{
		i = 0;
		while ((data->map)[i] != NULL)
			free((data->map)[i++]);
		free(data->map);
	}
}