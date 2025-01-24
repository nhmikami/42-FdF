/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naharumi <naharumi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 17:10:30 by naharumi          #+#    #+#             */
/*   Updated: 2025/01/24 11:09:13 by naharumi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fdf.h"

void	exit_error(char *msg, t_map *map)
{
	ft_putendl_fd(msg, 2);
	if (map)
		free_map(map);
	exit(EXIT_FAILURE);
	return ;
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

int	free_and_return(char **arr, char *str)
{
	if (arr)
		ft_free_arr(arr);
	if (str)
		free(str);
	return (0);
}

void	clear_gnl(int fd)
{
	char	*line;

	line = get_next_line(fd);
	while (line)
	{
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
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
