/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dtrig.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmotte <fmotte@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 11:01:27 by cpollock          #+#    #+#             */
/*   Updated: 2025/12/02 15:20:18 by fmotte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

double	dsin(double angle)
{
	return (sin(deg2rad(angle)));
}

double	dcos(double angle)
{
	return (cos(deg2rad(angle)));
}

double	dtan(double angle)
{
	return (tan(deg2rad(angle)));
}
