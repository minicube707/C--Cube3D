/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   point_math.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmotte <fmotte@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 10:36:42 by cpollock          #+#    #+#             */
/*   Updated: 2025/12/02 15:20:47 by fmotte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

double	point_angle(double x1, double y1, double x2, double y2)
{
	return (atan2(y2 - y1, x2 - x1));
}

double	point_dist(double x1, double y1, double x2, double y2)
{
	return (hypot(x2 - x1, y2 - y1));
}

double	vect_angle(t_vector vct1, t_vector vct2)
{
	return (atan2(vct2.y - vct1.y, vct2.x - vct1.x));
}

double	vect_dist(t_vector vct1, t_vector vct2)
{
	return (hypot(vct2.x - vct1.x, vct2.y - vct1.y));
}
