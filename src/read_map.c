/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naharumi <naharumi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 17:10:08 by naharumi          #+#    #+#             */
/*   Updated: 2025/01/22 17:23:15 by naharumi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fdf.h"

static int	map_width(char *str)
{
	int	count;

	count = 0;
	while (*str)
	{
		while (*str && ft_isspace(*str))
			str++;
		if (*str && !ft_isspace(*str))
			count++;
		while (*str && !ft_isspace(*str))
			str++;
	}
	return (count);
}

static int	validate_map(t_map *map, int fd)
{
	char	*line;

	line = get_next_line(fd);
	while (line)
	{
		if (map->width == 0)
			map->width = map_width(line);
		else if (map->width != map_width(line))
		{
			clear_gnl(fd);
			free(line);
			return (0);
		}
		map->height++;
		free(line);
		line = get_next_line(fd);
	}
	if (line)
		free(line);
	close(fd);
	return (1);
}

static int	init_map(t_map *map, int fd)
{
	int		i;

	map->width = 0;
	map->height = 0;
	if (!validate_map(map, fd))
		return (0);
	if (map->width == 0 || map->height == 0)
		return (0);
	map->matrix = (t_point **)malloc(sizeof(t_point *) * (map->height));
	if (!map->matrix)
		exit_error("Error: Failed to allocate memory for map matrix", NULL);
	i = 0;
	while (i < map->height)
	{
		map->matrix[i] = (t_point *)malloc(sizeof(t_point) * (map->width));
		if (!map->matrix[i])
			exit_error("Error: Failed to allocate memory for map row", map);
		i++;
	}
	return (1);
}

t_map	*read_map(char *file)
{
	int		fd;
	t_map	*map;

	fd = open(file, O_RDONLY);
	if (fd == -1)
		exit_error("Error: Failed to open file", NULL);
	map = malloc(sizeof(t_map));
	if (!map)
		exit_error("Error: Failed to allocate memory for map structure", NULL);
	if (!init_map(map, fd))
	{
		free(map);
		exit_error("Error: Invalid map", NULL);
	}
	fd = open(file, O_RDONLY);
	if (fd == -1)
		exit_error("Error: Failed to open file", map);
	if (!fill_matrix(map, fd))
	{
		clear_gnl(fd);
		exit_error("Error: Invalid map - point", map);
	}
	close(fd);
	return (map);
}
