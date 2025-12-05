/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_libft.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmotte <fmotte@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 16:28:11 by fmotte            #+#    #+#             */
/*   Updated: 2025/12/05 16:20:03 by fmotte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_isdigit(int c)
{
	if ('0' <= c && c <= '9')
		return (2048);
	return (0);
}

int	ft_isnum(char *string)
{
	int	i;

	i = 0;
	while (string[i] != '\0' && (string[i] == '-' || string[i] == '+' || !(33 <= string[i] && string[i] <= 126)))
		i++;
	if (string[i] == '\0' || !ft_isdigit(string[i]))
	{
		return (0);
	}
	while (string[i] != '\0' && ft_isdigit(string[i]))
		i++;
	while (string[i] != '\0' && !(33 <= string[i] && string[i] <= 126))
		i++;
	if (string[i] == 0)
		return (1);
	return (0);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (n == 0)
		return (0);
	while (s1[i] == s2[i] && s1[i] != 0 && s2[i] != 0 && i < n - 1)
		i++;
	return (((unsigned char)(s1[i])) - ((unsigned char)(s2[i])));
}

int	ft_atoi(const char *str)
{
	int	res;
	int	signe;

	res = 0;
	signe = 1;
	while (*str == 32 || (*str >= 9 && *str <= 13))
		str++;
	if (*str == 45)
	{
		signe = -1;
		str++;
	}
	else if (*str == 43)
		str++;
	while (48 <= *str && *str <= 57)
	{
		res *= 10;
		res += (*str - 48);
		str++;
	}
	res *= signe;
	return (res);
}

char	*ft_strdup(const char *src)
{
	char	*tab;
	int		len;
    int	i;
    
	len = ft_strlen(src);
	if (len == 0)
	{
		tab = malloc(sizeof(char));
		if (tab == NULL)
			return (NULL);
		tab[0] = 0;
		return (tab);
	}
	len++;
	tab = malloc(sizeof(char) * len);
	if (tab == NULL)
		return (NULL);
	i = -1;
	while (++i < len && src[i] != '\0')
		tab[i] = src[i];
	while (++i < len)
		tab[i] = '\0';
	return (tab);
}
