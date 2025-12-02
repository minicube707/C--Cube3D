/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dtrig.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpollock <cpollock@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 11:01:27 by cpollock          #+#    #+#             */
/*   Updated: 2025/12/02 11:01:40 by cpollock         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

double	deg2rad(double angle)
{
	return (fmod(angle * (PI / 180), PI * 2));
}

double	dsin(double angle)
{
	return(sin(deg2rad(angle)));
}

double	dcos(double angle)
{
	return(cos(deg2rad(angle)));
}

double	dtan(double angle)
{
	return(tan(deg2rad(angle)));
}