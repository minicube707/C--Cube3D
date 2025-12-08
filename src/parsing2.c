/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmotte <fmotte@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 15:12:29 by fmotte            #+#    #+#             */
/*   Updated: 2025/12/08 15:15:38 by fmotte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_extension(char *name_map, char *extention)
{
	int	len_map;
	int	len_ext;
	int	j;

	len_map = ft_strlen(name_map);
	len_ext = ft_strlen(extention);
	;
	j = 0;
	while (len_map - j > 0 && len_ext > j)
	{
		if (name_map[len_map - j] != extention[len_ext - j])
			break ;
		j++;
	}
	if (name_map[len_map - j] == extention[0])
		return (1);
	printf("Wrong extention. Can't open file %s\n", name_map);
	return (0);
}

int	clear_parsing(char **tab_map, char **tab_tex, char **tab_col)
{
	if (tab_map != NULL)
		tab_char_clear(tab_map);
	if (tab_tex != NULL)
		tab_char_clear(tab_tex);
	if (tab_col != NULL)
		tab_char_clear(tab_col);
	return (1);
}

int	fill_colour_texture(char *string, char ***tab_col)
{
	char	*tmp;

	tmp = skip_white_space(string);
	free(string);
	if (tmp == NULL)
		return (1);
	*tab_col = ft_realloc(*tab_col, tmp);
	return (0);
}

int	fill_information(char *string, char ***tab_tex, char ***tab_col)
{
	char	*tmp;

	tmp = skip_white_space(string);
	free(string);
	if (tmp[0] == '\0')
	{
		free(tmp);
		return (0);
	}
	if (ft_strncmp(tmp, "NO", 2) == 0)
		return (fill_colour_texture(tmp, tab_tex));
	else if (ft_strncmp(tmp, "SO", 2) == 0)
		return (fill_colour_texture(tmp, tab_tex));
	else if (ft_strncmp(tmp, "WE", 2) == 0)
		return (fill_colour_texture(tmp, tab_tex));
	else if (ft_strncmp(tmp, "EA", 2) == 0)
		return (fill_colour_texture(tmp, tab_tex));
	else if (ft_strncmp(tmp, "F", 1) == 0)
		return (fill_colour_texture(tmp, tab_col));
	else if (ft_strncmp(tmp, "C", 1) == 0)
		return (fill_colour_texture(tmp, tab_col));
	free(tmp);
	return (0);
}
