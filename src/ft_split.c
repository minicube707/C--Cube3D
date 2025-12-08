/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmotte <fmotte@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 12:12:39 by fmotte            #+#    #+#             */
/*   Updated: 2025/12/04 14:00:28 by fmotte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static	int	nb_sep(char const *s, char c)
{
	char	*tmp;
	int		nb_sep;

	nb_sep = 0;
	if (ft_strlen(s) == 0)
		return (0);
	if (s[0] == c)
		nb_sep--;
	if (s[ft_strlen(s) - 1] == c)
		nb_sep--;
	if (c == 0)
		return (2);
	tmp = ft_strchr(s, c);
	while (tmp != NULL)
	{
		if ((tmp != NULL) && (*(tmp + 1) != c))
			nb_sep++;
		tmp = ft_strchr(tmp + 1, c);
	}
	return (nb_sep + 2);
}

static char	*ft_nstrchr(const char *s, int c)
{
	int	i;

	i = 0;
	while (s[i] != 0)
	{
		if (s[i] != (char) c)
			return ((char *) &s[i]);
		i++;
	}
	if (c != '\0')
		return ((char *) &s[i]);
	return (NULL);
}

static void	error(char **tab, int index)
{
	while (index >= 0)
	{
		free(tab[index]);
		index--;
	}
	free(tab);
}

static char	**fill(char **tab, char *tmp, char c, int num_sep)
{
	char	*s1;
	char	*s2;
	int		len2;
	int		index;

	index = 0;
	while (index < num_sep - 1)
	{
		s1 = ft_nstrchr(tmp, c);
		s2 = ft_strchr(s1, c);
		if (s2 != NULL)
			len2 = ft_strlen(s2);
		else
			len2 = 0;
		tab[index] = ft_substr(s1, 0, ft_strlen(s1) - len2);
		if (tab[index] == NULL)
		{
			error(tab, index);
			return (NULL);
		}
		index++;
		tmp = s2;
	}
	return (tab);
}

char	**ft_split(char const *s, char c)
{
	int		num_sep;
	char	**tab;
	char	*tmp;

	num_sep = nb_sep(s, c);
	if (num_sep <= 0)
	{
		tab = malloc(sizeof(char **));
		if (tab == NULL)
			return (NULL);
		tab[0] = NULL;
		return (tab);
	}
	tmp = (char *) s;
	tab = malloc(num_sep * sizeof(char **));
	if (tab == NULL)
		return (NULL);
	tab = fill(tab, tmp, c, num_sep);
	if (tab == NULL)
		return (NULL);
	tab[num_sep - 1] = NULL;
	return (tab);
}
