#include "../inc/fdf.h"

// read_map
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

static int	validate_map(t_map *map, char *file)
{
	int		fd;
	char	*line;

	fd = open(file, O_RDONLY);
	if (fd == -1)
		exit_error("Error: Failed to open file", NULL);
	line = get_next_line(fd);
	while (line)
	{
		if (map->width == 0)
			map->width = map_width(line);
		else if (map->width != map_width(line))
		{
			close(fd);
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

static int	init_map(t_map *map, char *file)
{
	int		i;

	map->width = 0;
	map->height = 0;
	if (!validate_map(map, file))
		return (0);
	map->matrix = (t_point **)malloc(sizeof(t_point *) * (map->height));
	if (!map->matrix)
		exit_error("Error: Failed to allocate memory", NULL);
	i = 0;
	while (i < map->height)
	{
		map->matrix[i] = (t_point *)malloc(sizeof(t_point) * (map->width));
		if (!map->matrix[i])
		{
			exit_error("Error: Failed to allocate memory", map);
		}
		i++;
	}
	return (1);
}

t_map	*read_map(char *file)
{
	int		fd;
	t_map	*map;

	map = malloc(sizeof(t_map)); // malloc
	if (!map)
		exit_error("Error: Failed to allocate memory", NULL);
	if (!init_map(map, file))
	{
		free(map);
		exit_error("Error: Inconsistent map - collums", NULL);
	}
	fd = open(file, O_RDONLY);
	if (fd == -1)
	{
		exit_error("Error: Failed to open file", map);
	}
	if (!fill_matrix(map, fd))
	{
		exit_error("Error: Inconsistent map - point", map);
	}
	close(fd);
	return (map);
}
