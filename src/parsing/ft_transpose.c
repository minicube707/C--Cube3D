/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_transpose.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmotte <fmotte@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 13:37:24 by fmotte            #+#    #+#             */
/*   Updated: 2025/12/13 13:06:20 by fmotte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	ft_transpose_init(char **tab_map, int *height, int *width,
		char ***new_tab)
{
	*height = lenght_tab(tab_map);
	*width = get_width_map(tab_map);
	*new_tab = malloc(sizeof(char *) * ((*width) + 1));
	if (*new_tab == NULL)
		return (1);
	return (0);
}

static int	ft_transpose_loop(char ***new_tab, char **tab_map, int height,
		int i)
{
	int	j;

	j = 0;
	(*new_tab)[i] = malloc(sizeof(char) * height);
	if ((*new_tab)[i] == NULL)
	{
		tab_char_clear(*new_tab);
		return (1);
	}
	while (j <= height - 2)
	{
		if (ft_strlen(tab_map[j]) > i && tab_map[j][i] != '\n')
			(*new_tab)[i][j] = tab_map[j][i];
		else
			(*new_tab)[i][j] = ' ';
		j++;
	}
	(*new_tab)[i][j] = '\0';
	return (0);
}

char	**ft_transpose(char **tab_map)
{
	char	**new_tab;
	int		height;
	int		width;
	int		i;

	new_tab = NULL;
	if (ft_transpose_init(tab_map, &height, &width, &new_tab))
		return (NULL);
	i = 0;
	while (i < width)
	{
		if (ft_transpose_loop(&new_tab, tab_map, height, i))
			return (NULL);
		i++;
	}
	new_tab[i] = NULL;
	return (new_tab);
}
