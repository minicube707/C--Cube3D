/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmotte <fmotte@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/05 13:04:43 by fmotte            #+#    #+#             */
/*   Updated: 2025/12/05 13:37:30 by fmotte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int check_map_char(char **tab_map)
{
    int i;
    int j;
    int k;
    char *allow_string = "01NSEWD\n ";
    
    i = 0;
    while (tab_map[i] != NULL)
    {
        j = 0;
        while (tab_map[i][j] !='\0')
        {
            k = 0;
            while(allow_string[k] != '\0' && tab_map[i][j] != allow_string[k])
                k++;
            if (allow_string[k] =='\0')
                return (1);
            j++;
        }
        i++;
    }
    return (0);
}

int check_map(char **tab_map)   
{
    if(check_map_char(tab_map))
        return (1);
    //Check if only one player
    //Check pathfinding
    return (0);
}
