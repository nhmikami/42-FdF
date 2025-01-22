/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_matrix.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naharumi <naharumi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 17:10:44 by naharumi          #+#    #+#             */
/*   Updated: 2025/01/22 17:59:55 by naharumi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fdf.h"

static int	is_valid_int(char *str)
{
	long	value;
	int		sign;

	if (!str || !*str)
		return (0);
	sign = 1;
	value = 0;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	if (!*str)
		return (0);
	while (*str && *str != ',')
	{
		if (!(*str >= '0' && *str <= '9'))
			return (0);
		value = value * 10 + (*str - '0');
		if ((value * sign) < INT_MIN || (value * sign) > INT_MAX)
			return (0);
		str++;
	}
	return (1);
}

static int	is_valid_color(char *str)
{
	int	i;
	int	j;

	i = 0;
	while (str[i] && str[i] != ',')
		i++;
	if (!str[i])
		return (1);
	i++;
	if (str[i] != '0' || (str[i + 1] != 'x' && str[i + 1] != 'X')
		|| !str[i + 2])
		return (0);
	j = i + 2;
	while (str[j] && str[j] != '\n')
	{
		if (!((str[j] >= '0' && str[j] <= '9')
				|| (str[j] >= 'a' && str[j] <= 'f')
				|| (str[j] >= 'A' && str[j] <= 'F')))
			return (0);
		j++;
	}
	if (j - i > 8)
		return (0);
	return (1);
}

static int	get_color(char *str)
{
	int	color;

	color = 0;
	while (*str && *str != ',')
		str++;
	if (!*str)
		return (0xFFFFFF);
	str += 3;
	while (*str && ((*str >= '0' && *str <= '9') || (*str >= 'a' && *str <= 'f')
			|| (*str >= 'A' && *str <= 'F')))
	{
		color *= 16;
		if (*str >= '0' && *str <= '9')
			color += *str - '0';
		else if (*str >= 'a' && *str <= 'f')
			color += *str - 'a' + 10;
		else if (*str >= 'A' && *str <= 'F')
			color += *str - 'A' + 10;
		str++;
	}
	return (color);
}

static int	fill_point(t_map *map, int x, int y, char *str)
{
	if (!is_valid_int(str) || !is_valid_color(str))
		return (0);
	map->matrix[y][x].x = x;
	map->matrix[y][x].y = y;
	map->matrix[y][x].z = ft_atoi(str);
	map->matrix[y][x].color = get_color(str);
	return (1);
}

int	fill_matrix(t_map *map, int fd)
{
	int		x;
	int		y;
	char	*line;
	char	**aux;

	y = 0;
	while (y < map->height)
	{
		line = get_next_line(fd);
		aux = ft_split(line, ' ');
		if (!line || !aux)
			return (free_and_return(aux, line));
		x = 0;
		while (x < map->width)
		{
			if (!fill_point(map, x, y, aux[x]))
				return (free_and_return(aux, line));
			x++;
		}
		ft_free_arr(aux);
		free(line);
		y++;
	}
	return (1);
}
