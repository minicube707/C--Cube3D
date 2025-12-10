/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_raycast_hztl.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpollock <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 10:41:48 by cpollock          #+#    #+#             */
/*   Updated: 2025/12/10 10:41:54 by cpollock         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	compare_neighbors(t_game *data, t_vector vect);

bool	is_raycast_hztl(t_game *data, t_vector hztl, t_vector vtcl, bool prec)
{
	double	hztl_dist;
	double	vtcl_dist;
	int		ray_result;

	hztl_dist = vect_dist(data->player.pos, hztl);
	vtcl_dist = vect_dist(data->player.pos, vtcl);
	if (prec && fabs(hztl_dist - vtcl_dist) <= 0.01
		&& (hztl.y <= data->player.pos.y || vtcl.x <= data->player.pos.x))
	{
		ray_result = compare_neighbors(data, hztl);
		if (ray_result != 0)
			return (ray_result == 1 || ray_result == 2);
	}
	return (hztl_dist <= vtcl_dist);
}

static int	compare_neighbors(t_game *data, t_vector vect)
{
	double		angle;
	double		add;
	int			result;
	t_vector	dummy;

	angle = rad2deg(vect_angle(data->player.pos, vect));
	add = data->player.fov / W_WIDTH;
	result = raycast(data, &dummy, angle_limit(angle + add), false);
	if (result == raycast(data, &dummy, angle_limit(angle - add), false))
		return (result);
	return (0);
}
