/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmotte <fmotte@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 14:43:04 by fmotte            #+#    #+#             */
/*   Updated: 2025/12/09 15:44:09 by fmotte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	get_ori_player(char **tab_map)
{
	int		i;
	int		j;
	t_coord	coord;

	i = 0;
	coord.x = 0;
	coord.y = 0;
	while (tab_map[i] != NULL)
	{
		j = 0;
		while (tab_map[i][j] != '\0')
		{
			if (tab_map[i][j] == 'N')
				return (3);
			if (tab_map[i][j] == 'S')
				return (1);
			if (tab_map[i][j] == 'E')
				return (0);
			if (tab_map[i][j] == 'W')
				return (2);
			j++;
		}
		i++;
	}
	return (0);
}

t_coord	get_pos_player(char **tab_map)
{
	int		i;
	int		j;
	t_coord	coord;

	i = 0;
	coord.x = 0;
	coord.y = 0;
	while (tab_map[i] != NULL)
	{
		j = 0;
		while (tab_map[i][j] != '\0')
		{
			if (tab_map[i][j] == 'N' || tab_map[i][j] == 'S'
				|| tab_map[i][j] == 'E' || tab_map[i][j] == 'W')
			{
				coord.x = j;
				coord.y = i;
				return (coord);
			}
			j++;
		}
		i++;
	}
	return (coord);
}

int	in(t_stack *stack_path, int x, int y)
{
	t_stack	*tmp;

	tmp = stack_path;
	while (tmp != NULL)
	{
		if (tmp->coord->x == x && tmp->coord->y == y)
			return (1);
		tmp = tmp->next;
	}
	return (0);
}
