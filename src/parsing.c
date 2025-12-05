/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmotte <fmotte@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 14:58:28 by fmotte            #+#    #+#             */
/*   Updated: 2025/12/05 16:10:25 by fmotte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void print_info(char **tab_map, char **tab_tex)
{
    int i = 0;
    printf("Texture\n");
    while (tab_tex[i] != NULL)
    {
        printf("%s", tab_tex[i]);
        i++;
    }
    i = 0;
    printf("\nMAP\n");
    while (tab_map[i] != NULL)
    {
        printf("%s", tab_map[i]);
        i++;
    }
    printf("OK\n");
}

void clear_parsing(char **tab_map, char **tab_tex, char **tab_col)
{
    if (tab_map != NULL)
        tab_char_clear(tab_map);
    if (tab_tex != NULL)
        tab_char_clear(tab_tex);
    if (tab_col != NULL)
        tab_char_clear(tab_col);
}

int check_extension(char *name_map, char *extention)
{
    int len_map;
    int len_ext;
    int j;
    
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
    printf("Wrong extention. Can't open file %s\n", name_map);
    return (1);
}

static int fill_colour_texture(char *string, char ***tab_col)
{
    string = skip_white_space(string);
    *tab_col = ft_realloc(*tab_col, string);
    return (0);
}

static int fill_information(char *string, char ***tab_tex, char ***tab_col)
{
    char *tmp;
    
    tmp = skip_white_space(string);
    if (tmp[0] == '\0')
    {
        free(tmp);
        return (0);
    }
    if (ft_strncmp(tmp, "NO", 2) == 0)
        return (fill_colour_texture(tmp, tab_tex));
    else if (ft_strncmp(tmp, "SO", 2)  == 0)
        return (fill_colour_texture(tmp, tab_tex));
    else if (ft_strncmp(tmp, "WE", 2)  == 0)
        return (fill_colour_texture(tmp, tab_tex));
    else if (ft_strncmp(tmp, "EA", 2)  == 0)
        return (fill_colour_texture(tmp, tab_tex));
    else if (ft_strncmp(tmp, "F", 1)  == 0)
        return (fill_colour_texture(tmp, tab_col));
    else if (ft_strncmp(tmp, "C", 1)  == 0)
        return (fill_colour_texture(tmp, tab_col));
    free(tmp);
    return (0);

}


int check_data(char **tab_map, char **tab_tex, char **tab_col)
{
    if (tab_map == NULL || tab_tex == NULL || tab_col == NULL)
    {
        printf("KO Instruction\n"); 
        return (1);
    }  
    if (check_map(tab_map))
    {
        printf("KO Map\n"); 
        return (1);
    }  
    if (check_colour(tab_col))
    {
        printf("KO Colour\n"); 
        return (1);
    }  
    return (0);
}

int open_map(char *name_map)
{
    int fd;
    char *path;

    path = ft_strjoin("maps/good/", name_map);
    if (path ==  NULL)
    {
        printf("Error: fail malloc\n");
        return (-1); 
    }
    fd = open(path, O_RDONLY);
    free(path);
    if (fd > 2)
        return (fd);
    path = ft_strjoin("maps/bad/", name_map);
    if (path ==  NULL)
    {
        printf("Error: fail malloc\n");
        return (-1); 
    }
    fd = open(path, O_RDONLY);
    free(path);
    if (fd > 2)
        return (fd);
    printf("Error 404: %s file not found\n", name_map);
    return (-1);
}

void manage_data(int fd)
{
    /*TMP*/
    char *string;
    char **tab_map =  NULL;
    char **tab_tex =  NULL;
    char **tab_col =  NULL;
    
    string = "";
    while (string != NULL)
    {
        string = get_next_line(fd);
        if (string != NULL && lenght_tab(tab_col) == 3 && lenght_tab(tab_tex) == 5)
            tab_map = ft_realloc(tab_map, string);
        else if (string != NULL)
            fill_information(string, &tab_tex, &tab_col);
        //check if fill info fail ou realloc
    }
    if (check_data(tab_map, tab_tex, tab_col))
        return (clear_parsing(tab_map, tab_tex, tab_col));
    print_info(tab_map, tab_tex);      
    return (clear_parsing(tab_map, tab_tex, tab_col));
}

int parsing(char *name_map)
{
    int fd;
    
    if (check_extension(name_map, ".cub"))
		return (1);
	fd = open_map(name_map);
    if (fd == -1)
        return (1);
    manage_data(fd);
    return (0);
}
