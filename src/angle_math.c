/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   angle_math.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpollock <cpollock@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 10:40:17 by cpollock          #+#    #+#             */
/*   Updated: 2025/12/04 10:40:28 by cpollock         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

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
