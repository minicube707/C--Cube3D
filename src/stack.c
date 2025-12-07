/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: florent <florent@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/06 23:10:55 by florent           #+#    #+#             */
/*   Updated: 2025/12/07 01:01:32 by florent          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_stack	*new_stack(void)
{
	return (NULL);
}

int	is_empty_stack(t_stack *st)
{
	if (st == NULL)
		return (1);
	return (0);
}

t_stack	*push_stack(t_stack *st, int x, int y)
{
	t_stack	*element;
    t_coord *coord;
    
	element = malloc(sizeof(*element));
	if (element == NULL)
	{
		printf("Probleme allocation dynamique\n");
		return (NULL);
	}
    coord = malloc(sizeof(t_coord));
    if (element == NULL)
	{
		printf("Probleme allocation dynamique\n");
        free(element);
		return (NULL);
	}
    coord->x = x;
    coord->y = y;
	element->coord = coord;
	element->next = st;
	return (element);
}

t_stack	*clear_stack(t_stack *st)
{
	while ((!is_empty_stack(st)))
    {
        free(st->coord);    
        st = pop_stack(st);
    }
	return (new_stack());
}

t_stack	*pop_stack(t_stack *st)
{
	t_stack	*element;

	if (is_empty_stack(st))
		return (new_stack());
	element = st->next;
	free(st);
	return (element);
}