/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tab_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmotte <fmotte@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 16:45:31 by fmotte            #+#    #+#             */
/*   Updated: 2025/12/09 14:04:44 by fmotte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	tab_char_clear(char **tab)
{
	int	i;

	i = 0;
	if (tab == NULL)
		return ;
	while (tab[i] != NULL)
	{
		free(tab[i]);
		tab[i] = NULL;
		i++;
	}
	free(tab);
	tab = NULL;
}

int	lenght_tab(char **tab)
{
	int	nb_elem;

	if (tab == NULL)
		return (0);
	nb_elem = 0;
	while (tab[nb_elem] != NULL)
		nb_elem++;
	nb_elem++;
	return (nb_elem);
}
