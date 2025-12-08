/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   angle_math.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmotte <fmotte@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 10:40:17 by cpollock          #+#    #+#             */
/*   Updated: 2025/12/08 14:56:43 by fmotte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

double	deg2rad(double angle)
{
	return (fmod(angle * (PI / 180), PI * 2));
}

double	angle_limit(double angle)
{
	if (angle >= 0)
			angle = fmod(angle, 360);
	else
		angle = 360 + fmod(angle, 360);
	return (angle);
}
