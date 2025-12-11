/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_timer_ms.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpollock <cpollock@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 14:25:09 by cpollock          #+#    #+#             */
/*   Updated: 2025/12/11 14:25:20 by cpollock         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

double	add_timer_ms(struct timeval *time_src)
{
	struct timeval	time_cmp;
	double			time_diff;

	gettimeofday(&time_cmp, NULL);
	time_diff = (time_cmp.tv_sec * 1000) + (time_cmp.tv_usec / 1000);
	time_diff -= (time_src->tv_sec * 1000) + (time_src->tv_usec / 1000);
	time_src->tv_sec = time_cmp.tv_sec;
	time_src->tv_usec = time_cmp.tv_usec;
	return (time_diff);
}
