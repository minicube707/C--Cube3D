/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_basic.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpollock <cpollock@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/28 13:25:24 by cpollock          #+#    #+#             */
/*   Updated: 2025/11/28 13:25:36 by cpollock         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	draw_pixel(t_game *data, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || x >= W_WIDTH || y < 0 || y >= W_HEIGHT)
		return ;
	dst = data->addr + (y * data->line_len + x * (data->bbp / 8));
	*(unsigned int *)dst = color;
}

void	draw_rectangle(t_game *data, t_rectangle rect, int color)
{
	int	i;
	int	j;

	i = rect.x;
	while (i < rect.x + rect.width)
	{
		j = rect.y;
		while (j < rect.y + rect.height)
			draw_pixel(data, i, j++, color);
		i++;
	}
}

void	draw_line(t_game *data, t_vector vct1, t_vector vct2, int color)
{
	double	i;
	double	j;
	double	vect_ang;
	double	vect_dist;

	i = vct1.x;
	j = vct1.y;
	vect_ang = point_angle(i, j, vct2.x, vct2.y);
	vect_dist = point_dist(i, j, vct2.x, vct2.y);
	while (vect_dist > 0)
	{
		draw_pixel(data, i, j, color);
		i += cos(vect_ang);
		j += sin(vect_ang);
		vect_dist -= 1;
	}
}
