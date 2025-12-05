/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_colour.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmotte <fmotte@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/05 13:06:37 by fmotte            #+#    #+#             */
/*   Updated: 2025/12/05 17:48:00 by fmotte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

unsigned int	rgb2colour(unsigned int r, unsigned int g, unsigned int b)
{
	return ((0 << 24) | (r << 16) | (g << 8) | b);
}

int check_colour_rgb(char *string)
{
    int num;

    num = ft_atoi((string));
    if ((0 <= num && num <= 255))
        return (num);
    return (-1);
}

int extract_colour(char **tab_col, int index)
{
    char **tab_split;
    int r;
    int g;
    int b;
    
    tab_split = ft_split(tab_col[index], ',');
    if (tab_split == NULL)
        return (1);
    
    if (!ft_isnum((tab_split[0]+1)) || !ft_isnum((tab_split[1])) || !ft_isnum((tab_split[2])))
    {
        tab_char_clear(tab_split);
        return (1);
    }
    r = check_colour_rgb(tab_split[0]+1);
    g = check_colour_rgb(tab_split[1]);
    b = check_colour_rgb(tab_split[2]);
    tab_char_clear(tab_split);
    if (r == -1 || g == -1 || b == -1)
        return (1);
    printf("HEXA: %X\n", rgb2colour(r, g, b));
    return (0);   
}

int check_colour(char **tab_col)   
{
    printf("FLOOR\n");
    if (tab_col[0][0] == 'F')
    {
        printf("%s", tab_col[0]);
        if (extract_colour(tab_col, 0))
            return (1);
    }
    else
    {
        printf("%s", tab_col[1]);
        if (extract_colour(tab_col, 1))
            return (1);
    }
    
    printf("CELLING\n");
    if (tab_col[0][0] == 'C')
    {
        printf("%s", tab_col[0]);   
        if (extract_colour(tab_col, 0))
            return (1);
    }
    else
    {
        printf("%s", tab_col[1]);
        if (extract_colour(tab_col, 1))
            return (1);
    }
    return (0);
}

