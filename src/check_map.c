/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmotte <fmotte@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/05 13:04:43 by fmotte            #+#    #+#             */
/*   Updated: 2025/12/08 15:18:05 by fmotte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_stack	*parse_map(char **tab_map)
{
	int		i;
	int		j;
	t_stack	*stack;

	i = 0;
	stack = NULL;
	while (tab_map[i] != NULL)
	{
		j = 0;
		while (tab_map[i][j] != '\0')
		{
			if (tab_map[i][j] == '1')
			{
				stack = push_stack(stack, j, i);
				if (stack == NULL)
				{
					clear_stack(stack);
					return (NULL);
				}
			}
			j++;
		}
		i++;
	}
	return (stack);
}

int	get_width_map(char **tab_map)
{
	int	i;
	int	j;
	int	max_width;

	i = 0;
	max_width = 0;
	while (tab_map[i] != NULL)
	{
		j = 0;
		while (tab_map[i][j] != '\0')
			j++;
		if (j > max_width)
			max_width = j;
		i++;
	}
	return (max_width);
}

static int	check_map_player(char **tab_map)
{
	int	i;
	int	j;
	int	nb_player;

	i = 0;
	nb_player = 0;
	while (tab_map[i] != NULL)
	{
		j = 0;
		while (tab_map[i][j] != '\0')
		{
			if (tab_map[i][j] == 'N' || tab_map[i][j] == 'S'
				|| tab_map[i][j] == 'E' || tab_map[i][j] == 'W')
				nb_player++;
			j++;
		}
		i++;
	}
	if (nb_player == 1)
		return (0);
	return (1);
}

static int	check_map_char(char **tab_map)
{
	int		i;
	int		j;
	int		k;
	char	*allow_string;

	allow_string = "01NSEWD\n ";
	i = 0;
	while (tab_map[i] != NULL)
	{
		j = 0;
		while (tab_map[i][j] != '\0')
		{
			k = 0;
			while (allow_string[k] != '\0' && tab_map[i][j] != allow_string[k])
				k++;
			if (allow_string[k] == '\0')
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

int	check_map(char **tab_map)
{
	if (check_map_char(tab_map))
		return (1);
	if (check_map_player(tab_map))
		return (1);
	if (check_map_path(tab_map))
		return (1);
	return (0);
}
