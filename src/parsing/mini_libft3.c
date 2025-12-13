/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_libft3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmotte <fmotte@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 16:49:22 by fmotte            #+#    #+#             */
/*   Updated: 2025/12/13 13:11:51 by fmotte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_is_visible(char *string)
{
	int	i;

	i = 0;
	while (string[i] != '\0')
	{
		if (32 < string[i] && string[i] <= 126)
			return (1);
		i++;
	}
	return (0);
}

void	ft_substitute(char *string, int target, int new)
{
	int	i;

	i = 0;
	while (string[i] != '\0')
	{
		if (string[i] == target)
			string[i] = new;
		i++;
	}
}
