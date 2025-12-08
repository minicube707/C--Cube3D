/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmotte <fmotte@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 12:33:41 by cpollock          #+#    #+#             */
/*   Updated: 2025/12/02 15:20:52 by fmotte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
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
	strcpy((data->map)[0], "1111111111");
	strcpy((data->map)[1], "1000001001");
	strcpy((data->map)[2], "1000001001");
	strcpy((data->map)[3], "1000000000");
	strcpy((data->map)[4], "1011000000");
	strcpy((data->map)[5], "1000000001");
	strcpy((data->map)[6], "1000001001");
	strcpy((data->map)[7], "1000000001");
	strcpy((data->map)[8], "1000000001");
	strcpy((data->map)[9], "1000000001");
	strcpy((data->map)[10], "1000000001");
	strcpy((data->map)[11], "1000001001");
	strcpy((data->map)[12], "1000000101");
	strcpy((data->map)[13], "0000000101");
	strcpy((data->map)[14], "0000001101");
	strcpy((data->map)[15], "1000000001");
	strcpy((data->map)[16], "1110000001");
	strcpy((data->map)[17], "1110000001");
	strcpy((data->map)[18], "1110111111");
	data->col_floor = 0x1a1a1a;
	data->col_ceil = 0x454545;
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
