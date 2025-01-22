/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naharumi <naharumi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 17:09:58 by naharumi          #+#    #+#             */
/*   Updated: 2025/01/22 19:32:11 by naharumi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fdf.h"

static void	calculate_initial_zoom(t_data *data)
{
	float	width_zoom;
	float	height_zoom;
	float	rotated_width;
	float	rotated_height;

	rotated_width = fabs(data->map->width * cos(data->angle_z))
		+ fabs(data->map->height * sin(data->angle_z));
	rotated_height = fabs(data->map->width * sin(data->angle_z))
		+ fabs(data->map->height * cos(data->angle_z));
	width_zoom = (float)WINDOW_WIDTH / rotated_width * 0.8;
	height_zoom = (float)WINDOW_HEIGHT / rotated_height * 0.8;
	if (width_zoom < height_zoom)
		data->zoom = width_zoom;
	else
		data->zoom = height_zoom;
	if (data->zoom < 1)
		data->zoom = 1;
	if (data->zoom > 15)
		data->zoom = 15;
	printf("zoom = %d\n", data->zoom);
}

static void	center_map(t_data *data)
{
	float	rotated_width;
	float	rotated_height;

	rotated_width = fabs(data->map->width * cos(data->angle_z))
		+ fabs(data->map->height * sin(data->angle_z));
	rotated_height = fabs(data->map->width * sin(data->angle_z))
		+ fabs(data->map->height * cos(data->angle_z));
	data->offset_x = (WINDOW_WIDTH - (rotated_width * data->zoom)) / 2;
	data->offset_y = (WINDOW_HEIGHT - (rotated_height * data->zoom)) / 2;
	if (data->offset_x < 0)
		data->offset_x = 0;
	if (data->offset_y < 0)
		data->offset_y = 0;
	printf("offset x = %d, offset y = %d\n", data->offset_x, data->offset_y);
}

void	init_data(t_data *data)
{
	data->mlx = mlx_init();
	if (!data->mlx)
		exit_error("Error: Unable to initialize mlx", data->map);
	data->win = mlx_new_window(data->mlx, WINDOW_WIDTH, WINDOW_HEIGHT, "FdF");
	data->img = mlx_new_image(data->mlx, WINDOW_WIDTH - MENU_WIDTH,
			WINDOW_HEIGHT);
	data->adr = mlx_get_data_addr(data->img, &data->bpp, &data->size_line,
			&data->endian);
	data->angle_x = 0;
	data->angle_y = 0;
	data->angle_z = 0;
	data->projection = 0;
	data->mouse.is_pressed = 0;
	calculate_initial_zoom(data);
	center_map(data);
}

int	main(int ac, char **av)
{
	t_data	data;

	if (ac != 2)
		exit_error("Usage: ./fdf <map_file.fdf>", NULL);
	if (!check_extension(av[1]))
		exit_error("Error: Invalid file extension", NULL);
	data.map = read_map(av[1]);
	if (!data.map)
		exit_error("Error: Unable to load map", NULL);
	init_data(&data);
	draw_interface(&data);
	set_hooks(&data);
	mlx_loop(data.mlx);
	free_map(data.map);
	return (0);
}
// gcc src/*.c lib/*.c -Iincludes -Iminilibx-linux -Lminilibx-linux -lmlx -lm -lXext -lX11 -o test
