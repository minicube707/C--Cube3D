/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmotte <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 11:49:09 by fmotte            #+#    #+#             */
/*   Updated: 2025/05/14 17:48:21 by fmotte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static void	truncation(char *stock, char *res, char *occ)
{
	int	len_occ;
	int	len_res;
	int	len_to_copy;

	len_res = ft_strlen(res);
	len_occ = ft_strlen(occ);
	len_to_copy = len_res - len_occ + 1;
	ft_strncpy(stock, occ + 1, ft_strlen(occ + 1));
	stock[ft_strlen(occ + 1)] = '\0';
	res[len_to_copy] = '\0';
}

static void	reset_stock(char *stock, char **res)
{
	int		len_sto;
	int		len_to_copy;
	char	*occ;
	char	*tmp;

	occ = ft_strchr(stock, '\n');
	if (occ == NULL)
	{
		tmp = ft_strjoin(*res, stock);
		free(*res);
		*res = tmp;
		stock[0] = '\0';
		return ;
	}
	len_sto = ft_strlen(stock);
	len_to_copy = len_sto - ft_strlen(occ) + 1;
	free(*res);
	*res = malloc(len_to_copy + 1);
	if (*res == NULL)
		return ;
	ft_strncpy(*res, stock, len_to_copy);
	(*res)[len_to_copy] = '\0';
	ft_strncpy(stock, occ + 1, ft_strlen(occ + 1));
	stock[ft_strlen(occ + 1)] = '\0';
}

char	*end_loop(char *res, char *buffer, char *stock, int *first_loop)
{
	char	*tmp;
	char	*occ;

	occ = ft_strchr(buffer, '\n');
	if (occ != NULL)
		truncation(stock, buffer, occ);
	tmp = ft_strjoin(res, buffer);
	free(buffer);
	if (tmp == NULL)
	{
		free(res);
		return (NULL);
	}
	free(res);
	res = tmp;
	*first_loop = 1;
	return (res);
}

char	*loop(int fd, char *res, char *stock, int first_loop)
{
	int		nb_read;
	char	*buffer;

	while (!ft_strchr(res, '\n'))
	{
		buffer = malloc(BUFFER_SIZE + 1);
		if (buffer == NULL)
			return (NULL);
		nb_read = read(fd, buffer, BUFFER_SIZE);
		if (nb_read <= 0)
		{
			free(buffer);
			if (nb_read == 0 && first_loop == 1)
				return (res);
			free(res);
			return (NULL);
		}
		buffer[nb_read] = '\0';
		res = end_loop(res, buffer, stock, &first_loop);
		if (res == NULL)
			return (NULL);
	}
	return (res);
}

char	*get_next_line(int fd)
{
	int			first_loop;
	static char	stock[BUFFER_SIZE + 1];
	char		*res;

	if (fd < 0)
		return (NULL);
	first_loop = 0;
	res = malloc(1);
	if (res == NULL)
		return (NULL);
	ft_strncpy(res, "", 1);
	if (ft_strlen(stock) != 0)
	{
		reset_stock(stock, &res);
		first_loop = 1;
	}
	res = loop(fd, res, stock, first_loop);
	return (res);
}
