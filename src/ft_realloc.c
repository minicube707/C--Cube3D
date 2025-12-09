/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmotte <fmotte@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/24 13:10:42 by fmotte            #+#    #+#             */
/*   Updated: 2025/12/09 14:03:46 by fmotte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static char	**ft_realloc_short(char **tab, char *string)
{
	char	**new_tab;

	new_tab = malloc(sizeof(char *) * 2);
	if (new_tab == NULL)
	{
		free(tab);
		return (NULL);
	}
	new_tab[0] = string;
	new_tab[1] = NULL;
	return (new_tab);
}

static char	**ft_realloc_utils_utils(char **newtab, char **tab, char *string)
{
	int	i;

	i = -1;
	while (tab[++i] != NULL)
		newtab[i] = tab[i];
	free(tab);
	newtab[i] = string;
	newtab[i + 1] = NULL;
	return (newtab);
}

char	**ft_realloc(char **tab, char *string)
{
	char	**new_tab;

	if (string == NULL)
		return (NULL);
	if (tab == NULL)
	{
		new_tab = ft_realloc_short(tab, string);
		return (new_tab);
	}
	new_tab = malloc((lenght_tab(tab) + 1) * sizeof(char *));
	if (new_tab == NULL)
	{
		tab_char_clear(tab);
		return (NULL);
	}
	new_tab = ft_realloc_utils_utils(new_tab, tab, string);
	return (new_tab);
}
