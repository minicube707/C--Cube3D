/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_arrow.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpollock <cpollock@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/05 14:32:12 by cpollock          #+#    #+#             */
/*   Updated: 2025/12/05 14:32:29 by cpollock         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static void	arrow2(t_game *data, t_arrow arrow, t_vector middle, int color);

void	draw_arrow(t_game *data, t_arrow arrow, int color)
{
	t_vector	arrow_top;
	t_vector	arrow_middle;

	vect_add(&arrow_top, arrow.pos, arrow.angle, arrow.height / 2);
	vect_add(&arrow_middle, arrow.pos, arrow.angle, -(arrow.height / 2));
	draw_line(data, arrow_middle, arrow_top, color);
	arrow2(data, arrow, arrow_middle, color);
}

static void	arrow2(t_game *data, t_arrow arrow, t_vector middle, int color)
{
	t_vector	next_top;
	t_vector	next_middle;
	double		next_height;
	double		end_angle;
	double		i;

	end_angle = atan2(arrow.height, arrow.width / 2);
	i = 0.25;
	while (i <= arrow.width / 2)
	{
		next_height = tan(end_angle) * ((arrow.width / 2) - i);
		vect_add(&next_middle, middle, arrow.angle + PI / 2, i);
		vect_add(&next_top, next_middle, arrow.angle, next_height);
		draw_line(data, next_middle, next_top, color);
		vect_add(&next_middle, middle, arrow.angle - PI / 2, i);
		vect_add(&next_top, next_middle, arrow.angle, next_height);
		draw_line(data, next_middle, next_top, color);
		i += 0.25;
	}
}
