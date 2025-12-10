/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_libft2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmotte <fmotte@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 16:16:52 by fmotte            #+#    #+#             */
/*   Updated: 2025/12/10 17:00:46 by fmotte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	*skip_white_space(char *string)
{
	int		i;
	char	*res;

	i = 0;
	while (string[i] != '\0' && !(32 < string[i] && string[i] <= 126))
		i++;
	res = ft_substr(string, i, ft_strlen(string));
	return (res);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	size;
	size_t	i;
	char	*p;
	size_t	min;

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

int ft_perror(char *string)
{
	write(2, "Error\n", 6);
	write(2, string, ft_strlen(string));
	return (1);
}

void	*ft_bzero(void *ptr, size_t num)
{
	size_t			i;
	unsigned char	*p;

	i = 0;
	p = (unsigned char *) ptr;
	while (i < num)
	{
		p[i] = (unsigned char) 0;
		i++;
	}
	return (ptr);
}

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	len_dst;
	size_t	len_src;

	i = 0;
	len_dst = 0;
	len_src = 0;
	while (dst[len_dst] != 0 && len_dst < size)
		len_dst++;
	while (src[len_src] != 0)
		len_src++;
	if (len_dst >= size)
		return (size + len_src);
	while ((len_dst + i + 1 < size) && src[i] != 0)
	{
		dst[len_dst + i] = src[i];
		i++;
	}
	if (len_dst + i < size)
		dst[len_dst + i] = 0;
	return (len_dst + len_src);
}
