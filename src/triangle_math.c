/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   triangle_math.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpollock <cpollock@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 10:36:42 by cpollock          #+#    #+#             */
/*   Updated: 2025/12/01 10:36:54 by cpollock         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

double	deg2rad(double angle)
{
	return (angle * (PI / 180));
}

double	point_angle(double x1, double y1, double x2, double y2)
{
	return (atan2(y2 - y1, x2 - x1));
}

double	point_dist(double x1, double y1, double x2, double y2)
{
	return (hypot(x2 - x1, y2 - y1));
}
