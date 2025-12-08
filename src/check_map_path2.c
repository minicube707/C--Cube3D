/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map_path2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmotte <fmotte@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 14:40:48 by fmotte            #+#    #+#             */
/*   Updated: 2025/12/08 14:41:53 by fmotte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	clear_map(t_stack *stack_wall, t_stack **stack_path, t_stack **stack_save)
{
	if (stack_wall != NULL)
		clear_stack(stack_wall);
	if (stack_path != NULL)
		clear_stack(*stack_path);
	if (stack_save != NULL)
		clear_stack(*stack_save);
	return (1);
}
