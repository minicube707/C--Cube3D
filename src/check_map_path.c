/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map_path.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmotte <fmotte@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 14:01:12 by fmotte            #+#    #+#             */
/*   Updated: 2025/12/08 15:46:37 by fmotte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	add_path(t_stack **stack_path, t_stack **stack_save, int x, int y)
{
	*stack_save = push_stack(*stack_save, x, y);
	if (*stack_save == NULL)
		return (1);
	*stack_path = push_stack(*stack_path, x, y);
	if (*stack_path == NULL)
		return (1);
	return (0);
}

static int	chech_path_x(t_stack *stack_wall, t_stack **stack_path,
		t_stack **stack_save, int max)
{
	t_coord	*node;
	int		delta[2];
	int		i;

	delta[0] = -1;
	delta[1] = 1;
	i = 0;
	node = (*stack_path)->coord;
	while (i < 2)
	{
		if (!in(stack_wall, node->x + delta[i], node->y) && !in(*stack_save,
				node->x + delta[i], node->y))
		{
			if (0 < node->x + delta[i] && node->x + delta[i] < max)
			{
				if (add_path(stack_path, stack_save, node->x + delta[i],
						node->y))
					return (1);
			}
			else
				return (clear_map(stack_wall, stack_path, stack_save));
		}
		i++;
	}
	return (0);
}

static int	chech_path_y(t_stack *stack_wall, t_stack **stack_path,
		t_stack **stack_save, int max)
{
	t_coord	*node;
	int		delta[2];
	int		i;

	delta[0] = -1;
	delta[1] = 1;
	i = 0;
	node = (*stack_path)->coord;
	while (i < 2)
	{
		if (!in(stack_wall, node->x, node->y + delta[i]) && !in(*stack_save,
				node->x, node->y + delta[i]))
		{
			if (0 < node->y + delta[i] && node->y + delta[i] < max)
			{
				if (add_path(stack_path, stack_save, node->x, node->y
						+ delta[i]))
					return (1);
			}
			else
				return (clear_map(stack_wall, stack_path, stack_save));
		}
		i++;
	}
	return (0);
}

static int	check_map_path_init(t_stack **stack_path, t_stack **stack_wall,
		t_coord *max_limit, char **tab_map)
{
	t_coord	pos_player;
	int		max_width;
	int		max_height;

	*stack_wall = parse_map(tab_map);
	if (*stack_wall == NULL)
		return (1);
	pos_player = get_pos_player(tab_map);
	*stack_path = push_stack(*stack_path, pos_player.x, pos_player.y);
	if (*stack_path == NULL)
	{
		clear_stack(*stack_wall);
		return (1);
	}
	max_width = get_width_map(tab_map);
	max_height = lenght_tab(tab_map);
	max_limit->x = max_width;
	max_limit->y = max_height;
	return (0);
}

int	check_map_path(char **tab_map, t_game *data)
{
	t_stack	*stack_path;
	t_stack	*stack_save;
	t_stack	*stack_wall;
	t_coord	*node;
	t_coord	max_limit;

	stack_path = NULL;
	stack_save = NULL;
	if (check_map_path_init(&stack_path, &stack_wall, &max_limit, tab_map))
		return (1);
	data->map_height = max_limit.y;
	data->map_width = max_limit.x;
	while (!is_empty_stack(stack_path))
	{
		while (!is_empty_stack(stack_path))
		{
			if (chech_path_x(stack_wall, &stack_path, &stack_save, max_limit.x))
				return (1);
			if (chech_path_y(stack_wall, &stack_path, &stack_save, max_limit.y))
				return (1);
			node = stack_path->coord;
			stack_path = pop_stack(stack_path);
			free(node);
		}
	}
	clear_map(stack_wall, NULL, &stack_save);
	return (0);
}
