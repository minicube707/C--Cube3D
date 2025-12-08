/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_texture.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmotte <fmotte@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/05 16:30:59 by fmotte            #+#    #+#             */
/*   Updated: 2025/12/08 15:18:31 by fmotte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	check_texture_path(char *string)
{
	char	*tmp;

	tmp = skip_white_space(string);
	if (ft_strncmp(tmp, "textures/", 8) != 0)
	{
		free(tmp);
		return (1);
	}
	if (!check_extension(tmp, ".xpm\n"))
	{
		free(tmp);
		return (1);
	}
	free(tmp);
	return (0);
}

static int	chec_texture_utils(char *tab_string, char *string, int j)
{
	char	*sub_string;

	sub_string = ft_substr(tab_string, j * 2, 2);
	if (sub_string == NULL)
		return (1);
	if (ft_strncmp(string, sub_string, 2) == 0)
	{
		if (check_texture_path(string + 2))
		{
			free(sub_string);
			return (1);
		}
	}
	free(sub_string);
	return (0);
}

int	chec_texture(char **tab_tex)
{
	char	*tab_string;
	int		i;
	int		j;

	tab_string = "NOSOWEEA";
	i = 0;
	while (i < 4)
	{
		j = 0;
		while (j < 4)
		{
			if (chec_texture_utils(tab_string, tab_tex[i], j))
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}
