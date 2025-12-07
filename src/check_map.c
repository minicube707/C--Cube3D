/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: florent <florent@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/05 13:04:43 by fmotte            #+#    #+#             */
/*   Updated: 2025/12/07 01:49:08 by florent          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_stack *parse_map(char **tab_map)
{
    int i;
    int j;
    t_stack *stack;
    
    i = 0;
    stack = NULL;
    while (tab_map[i] != NULL)
    {
        j = 0;
        while (tab_map[i][j] != '\0')
        {
            if (tab_map[i][j] == '1')
            {
                stack = push_stack(stack, j, i);
                // verif fail mallock
            }
            j++;
        }
        i++;
    }
    return (stack);
}

t_coord get_pos_player(char **tab_map)
{
    int i;
    int j;
    t_coord coord;
    
    i = 0;
    coord.x = 0;
    coord.y = 0;
    while (tab_map[i] != NULL)
    {
        j = 0;
        while (tab_map[i][j] != '\0')
        {
            if (tab_map[i][j] == 'N' || tab_map[i][j] == 'S' || tab_map[i][j] == 'E' || tab_map[i][j] == 'W')
            {
                coord.x = j;    
                coord.y = i;
                return (coord);         
            }
            j++;
        }
        i++;
    }
    return (coord);
}
int in(t_stack *stack_path, int x, int y)
{  
    t_stack *tmp;
    
    tmp = stack_path;
    while (tmp != NULL)
    {
        if (tmp->coord->x == x && tmp->coord->y ==  y)
            return (1);
        tmp = tmp->next;
    }
    return (0);
}

int get_width_map(char **tab_map)
{
    int i;
    int j;
    int max_width;
    
    i = 0;
    max_width = 0;
    while (tab_map[i] != NULL)
    {
        j = 0;
        while (tab_map[i][j] != '\0')
            j++;
        if (j > max_width)
            max_width = j;
        i++;
    }
    return (max_width);
}

int check_map_path(char **tab_map)
{
    t_stack *stack_wall;
    t_stack *stack_path;
    t_stack *stack_tmp;
    t_stack *stack_save;
    t_coord pos_player;
    t_coord *node;
    int     max_width;
    int     max_height;
    
    stack_path = NULL;
    stack_tmp = NULL;
    stack_save = NULL;
    stack_wall = parse_map(tab_map);
    pos_player = get_pos_player(tab_map);
    stack_path = push_stack(stack_path, pos_player.x, pos_player.y);
    
    max_width = get_width_map(tab_map);
    max_height = lenght_tab(tab_map);
    
    while (!is_empty_stack(stack_path))
    {
        while (!is_empty_stack(stack_path))
        {
            node = stack_path->coord;
            stack_path = pop_stack(stack_path);
            
            if (!in(stack_wall, node->x + 1, node->y) && !in(stack_save, node->x + 1, node->y))
            {
                if (node->x + 1 < max_width)
                {
                    stack_save = push_stack(stack_save, node->x + 1, node->y);
                    stack_tmp = push_stack(stack_tmp, node->x + 1, node->y);
                }
                    
                else
                {
                    printf("KO X:%d Y:%d\n", node->x +1, node->y);
                    clear_stack(stack_wall);
                    clear_stack(stack_path);
                    clear_stack(stack_save);
                    clear_stack(stack_tmp);
                    free(node);
                    return (1);
                }
            }
           
            if (!in(stack_wall, node->x - 1, node->y) && !in(stack_save, node->x - 1, node->y))
            {
                if (0 < node->x - 1)
                {
                    stack_save = push_stack(stack_save, node->x - 1, node->y);
                    stack_tmp = push_stack(stack_tmp, node->x - 1, node->y);
                } 
                else
                {
                    printf("KO X:%d Y:%d\n", node->x -1, node->y);
                    clear_stack(stack_wall);
                    clear_stack(stack_path);
                    clear_stack(stack_save);
                    clear_stack(stack_tmp);
                    free(node);
                    return (1);
                }
            }
            
            if (!in(stack_wall, node->x, node->y + 1) && !in(stack_save, node->x, node->y + 1))
            {
                if (node->y + 1 < max_height)
                {
                    stack_save = push_stack(stack_save, node->x, node->y + 1);
                    stack_tmp = push_stack(stack_tmp, node->x, node->y + 1);
                }  
                else
                {
                    printf("KO X:%d Y:%d\n", node->x, node->y + 1);
                    clear_stack(stack_wall);
                    clear_stack(stack_path);
                    clear_stack(stack_save);
                    clear_stack(stack_tmp);
                    free(node);
                    return (1);
                }
            }
            
            if (!in(stack_wall, node->x, node->y - 1) && !in(stack_save, node->x, node->y - 1))
            {
                if (0 < node->y - 1)
                {
                    stack_save = push_stack(stack_save, node->x, node->y - 1);
                    stack_tmp = push_stack(stack_tmp, node->x, node->y - 1);
                }
                else
                {
                    printf("KO X:%d Y:%d\n", node->x, node->y - 1);
                    clear_stack(stack_wall);
                    clear_stack(stack_path);
                    clear_stack(stack_save);
                    clear_stack(stack_tmp);
                    free(node);
                    return (1);
                }
            }
            free(node);
        }
        stack_path = stack_tmp;
        stack_tmp = NULL;
    }
    clear_stack(stack_wall);
    clear_stack(stack_save);
    return (0);
}

int check_map_player(char **tab_map)
{
    int i;
    int j;
    int nb_player;
    
    i = 0;
    nb_player = 0;
    while (tab_map[i] != NULL)
    {
        j = 0;
        while (tab_map[i][j] != '\0')
        {
            if (tab_map[i][j] == 'N' || tab_map[i][j] == 'S' || tab_map[i][j] == 'E' || tab_map[i][j] == 'W')
                nb_player++;
            j++;
        }
        i++;
    }
    if (nb_player == 1)
        return (0);
    return (1);
}

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
    if (check_map_player(tab_map))
        return (1);
    if (check_map_path(tab_map))
        return (1);
    return (0);
}
