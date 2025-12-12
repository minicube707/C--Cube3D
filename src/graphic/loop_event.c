/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop_event.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmotte <fmotte@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/28 15:29:25 by cpollock          #+#    #+#             */
/*   Updated: 2025/12/02 15:20:31 by fmotte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	loop_event(t_game *data)
{
	data->ms_fps += add_timer_ms(&(data->time_fps));
	if (data->ms_fps > 1000 / FPS)
	{
		data->ms_fps = fmod(data->ms_fps, 1000 / FPS);
		data->ms_anim += add_timer_ms(&(data->time_anim));
		data->ms_anim = fmod(data->ms_anim, ANIM_MS);
		if (data->player.key_space_pressed)
			door_check(data, &data->player);
		data->player.key_space_pressed = false;
		door_anim(data);
		turn_player(&data->player);
		move_player(data, &data->player);
		render_raycast(data, data->player);
		draw_minimap(data);
		mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
	}
	return (0);
}
