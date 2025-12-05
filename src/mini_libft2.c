/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_libft2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmotte <fmotte@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 16:16:52 by fmotte            #+#    #+#             */
/*   Updated: 2025/12/05 15:59:16 by fmotte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char *skip_white_space(char *string)
{
    int i;
    char *res;
    
    i = 0;
    while (string[i] != '\0' && !(32 < string[i] && string[i] <= 126))
        i++;
    res = ft_substr(string, i, ft_strlen(string));
    free(string);
    return (res);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t		size;
	size_t		i;
	char		*p;
	size_t		min;

	i = 0;
	size = 0;
	min = len;
	if (s == NULL)
		return (NULL);
	size = ft_strlen(s);
	if (start >= size)
		return (ft_strdup(""));
	if (size - start < len)
		min = size - start;
	p = malloc((min + 1) * sizeof(char));
	if (p == NULL)
		return (NULL);
	while (i < min)
	{
		p[i] = s[i + start];
		i++;
	}
	p[i] = 0;
	return (p);
}
