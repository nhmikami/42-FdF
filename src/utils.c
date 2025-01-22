#include "../inc/fdf.h"

void	exit_error(char *msg, t_map *map)
{
	ft_putendl_fd(msg, 2);
	if (map)
		free_map(map);
	exit(EXIT_FAILURE);
}

void	free_map(t_map *map)
{
	int	i;

	if (map)
	{
		if (map->matrix)
		{
			i = 0;
			while (i < map->height)
			{
				if (map->matrix[i])
				{
					free(map->matrix[i]);
					map->matrix[i] = NULL;
				}
				i++;
			}
			free(map->matrix);
		}
		free(map);
	}
	return ;
}

int	check_extension(char *file)
{
	int	len;

	len = ft_strlen(file);
	if (ft_strncmp(&file[len - 4], ".fdf", 4) == 0)
		return (1);
	return (0);
}

void	ft_bzero(void *s, size_t n)
{
	unsigned char	*ptr;
	size_t			i;

	ptr = (unsigned char *)s;
	i = 0;
	while (i < n)
	{
		ptr[i] = 0;
		i++;
	}
}
