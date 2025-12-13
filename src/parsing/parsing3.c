/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmotte <fmotte@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 18:24:27 by fmotte            #+#    #+#             */
/*   Updated: 2025/12/13 12:59:54 by fmotte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	manage_data_loop(char ***tab_map, char ***tab_tex, char ***tab_col,
		char *string)
{
	if (string != NULL && lenght_tab(*tab_col) == 3
		&& (lenght_tab(*tab_tex) == 5 || lenght_tab(*tab_tex) == 6))
	{
		ft_substitute(string, '0', ' ');
		ft_substitute(string, '\n', ' ');
		*tab_map = ft_realloc(*tab_map, string);
		if (*tab_map == NULL)
		{
			free(string);
			return (clear_parsing(*tab_map, *tab_tex, *tab_col));
		}
	}
	else if (string != NULL)
	{
		if (fill_information(string, tab_tex, tab_col))
			return (clear_parsing(*tab_map, *tab_tex, *tab_col));
	}
	return (0);
}
