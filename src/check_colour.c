/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_colour.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmotte <fmotte@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/05 13:06:37 by fmotte            #+#    #+#             */
/*   Updated: 2025/12/08 15:39:04 by fmotte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static unsigned int	rgb2colour(unsigned int r, unsigned int g, unsigned int b)
{
	return ((0 << 24) | (r << 16) | (g << 8) | b);
}

static int	check_colour_rgb(char *string)
{
	int	num;

	num = ft_atoi((string));
	if ((0 <= num && num <= 255))
		return (num);
	return (-1);
}

static int	extract_colour(t_game *data, char **tab_col, int index, char where)
{
	char	**tab_split;
	int		r;
	int		g;
	int		b;

	tab_split = ft_split(tab_col[index], ',');
	if (tab_split == NULL)
		return (1);
	if (!ft_isnum((tab_split[0] + 1)) || !ft_isnum((tab_split[1]))
		|| !ft_isnum((tab_split[2])))
	{
		tab_char_clear(tab_split);
		return (1);
	}
	r = check_colour_rgb(tab_split[0] + 1);
	g = check_colour_rgb(tab_split[1]);
	b = check_colour_rgb(tab_split[2]);
	tab_char_clear(tab_split);
	if (r == -1 || g == -1 || b == -1)
		return (1);
	if (where == 'F')
		data->col_floor = rgb2colour(r, g, b);
	else
		data->col_ceil = rgb2colour(r, g, b);
	return (0);
}

int	check_colour(char **tab_col, t_game *data)
{
	if (tab_col[0][0] == 'F')
	{
		if (extract_colour(data, tab_col, 0, 'F'))
			return (1);
	}
	else
	{
		if (extract_colour(data, tab_col, 1, 'F'))
			return (1);
	}
	if (tab_col[0][0] == 'C')
	{
		if (extract_colour(data, tab_col, 0, 'C'))
			return (1);
	}
	else
	{
		if (extract_colour(data, tab_col, 1, 'C'))
			return (1);
	}
	return (0);
}
