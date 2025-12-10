/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmotte <fmotte@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/06 23:10:55 by florent           #+#    #+#             */
/*   Updated: 2025/12/10 15:31:52 by fmotte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	is_empty_stack(t_stack *st)
{
	if (st == NULL)
		return (1);
	return (0);
}

t_stack	*push_stack_utils(t_stack *st, t_coord *coord, t_stack *element)
{
	t_stack	*start;

	element->coord = coord;
	element->next = NULL;
	if (st == NULL)
		return (element);
	start = st;
	while (st->next != NULL)
		st = st->next;
	st->next = element;
	return (start);
}

t_stack	*push_stack(t_stack *st, int x, int y)
{
	t_stack	*element;
	t_coord	*coord;

	element = malloc(sizeof(t_stack));
	if (element == NULL)
	{
		clear_stack(st);
		ft_perror("Probleme allocation dynamique\n");
		return (NULL);
	}
	coord = malloc(sizeof(t_coord));
	if (element == NULL)
	{
		clear_stack(st);
		ft_perror("Probleme allocation dynamique\n");
		free(element);
		return (NULL);
	}
	coord->x = x;
	coord->y = y;
	return (push_stack_utils(st, coord, element));
}

t_stack	*clear_stack(t_stack *st)
{
	while ((!is_empty_stack(st)))
	{
		free(st->coord);
		st = pop_stack(st);
	}
	return (NULL);
}

t_stack	*pop_stack(t_stack *st)
{
	t_stack	*element;

	if (is_empty_stack(st))
		return (NULL);
	element = st->next;
	free(st);
	return (element);
}
