/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vect_math.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmotte <fmotte@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 11:37:37 by cpollock          #+#    #+#             */
/*   Updated: 2025/12/02 15:20:59 by fmotte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	vect_add(t_vector *dest, t_vector src, double angle, double dist)
{
	dest->x = src.x + cos(angle) * dist;
	dest->y = src.y + sin(angle) * dist;
}
