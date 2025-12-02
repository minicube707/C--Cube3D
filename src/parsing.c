/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmotte <fmotte@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 14:58:28 by fmotte            #+#    #+#             */
/*   Updated: 2025/12/02 18:14:44 by fmotte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int check_expand(char *name_map)
{
    int len_map;
    int len_ext;
    int j;
    char *extention;
    
    extention = ".cub";
    len_map = ft_strlen(name_map);
    len_ext = 4;
    j = 0;
    while(len_map - j > 0 && len_ext > j)
    {
        if (name_map[len_map - j] != extention[len_ext - j])
            break;
        j++;
    }
    if (name_map[len_map - j] == '.')
        return(0);
    printf("Wrong extention. Can't open file\n");
    return (1);
}

void open_map(char *name_map)
{
    int fd;
    char *path;

    path = ft_strjoin("map/", name_map);
    if (path ==  NULL)
        return ;
    fd = open(path, O_RDONLY);
    free(path);
    
    char *string;
    string = "";
    
    char **tab_map =  NULL;
    while (string != NULL)
    {
        string = get_next_line(fd);
        if (string != NULL && ft_isdigit(string[0]))
            tab_map = ft_realloc(tab_map, string);
        else
            free(string);
    }
    int i = 0;
    while (tab_map[i] != NULL)
    {
        printf("%s", tab_map[i]);
        i++;
    }
    tab_char_clear(tab_map);
}