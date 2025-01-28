/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mlx.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naharumi <naharumi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 10:51:22 by naharumi          #+#    #+#             */
/*   Updated: 2025/01/24 11:01:57 by naharumi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fdf.h"

static void	get_bounds(t_data *data, t_bounds *bounds)
{
	int		x;
	int		y;
	t_point	proj;

	bounds->min_x = (float)INT_MAX;
	bounds->max_x = (float)INT_MIN;
	bounds->min_y = (float)INT_MAX;
	bounds->max_y = (float)INT_MIN;
	y = -1;
	while (++y < data->map->height)
	{
		x = -1;
		while (++x < data->map->width)
		{
			proj = project_point(data->map->matrix[y][x], data);
			if (proj.x < bounds->min_x)
				bounds->min_x = proj.x;
			if (proj.x > bounds->max_x)
				bounds->max_x = proj.x;
			if (proj.y < bounds->min_y)
				bounds->min_y = proj.y;
			if (proj.y > bounds->max_y)
				bounds->max_y = proj.y;
		}
	}
}

static void	initial_zoom(t_data *data)
{
	t_bounds	bounds;
	float		width_zoom;
	float		height_zoom;

	get_bounds(data, &bounds);
	width_zoom = (float)(WINDOW_WIDTH - MENU_WIDTH)
		/ (bounds.max_x - bounds.min_x);
	height_zoom = (float)WINDOW_HEIGHT / (bounds.max_y - bounds.min_y);
	if (width_zoom < height_zoom)
		data->zoom = width_zoom;
	else
		data->zoom = height_zoom;
	if (data->zoom < 1)
		data->zoom = 1;
	if (data->zoom > 15)
		data->zoom = 15;
	return ;
}

static void	center_map(t_data *data)
{
	t_bounds	bounds;

	get_bounds(data, &bounds);
	if (data->zoom == 15)
	{
		data->offset_x = (WINDOW_WIDTH - MENU_WIDTH) / 2;
		data->offset_y = WINDOW_HEIGHT / 2;
	}
	else
	{
		data->offset_x = ((WINDOW_WIDTH - MENU_WIDTH)
				- (bounds.max_x - bounds.min_x) * data->zoom) / 2
			- bounds.min_x * data->zoom;
		data->offset_y = (WINDOW_HEIGHT - (bounds.max_y - bounds.min_y)
				* data->zoom) / 2 - bounds.min_y * data->zoom;
	}
	if (data->offset_x < 0)
		data->offset_x = 0;
	if (data->offset_y < 0)
		data->offset_y = 0;
	return ;
}

void	init_data(t_data *data)
{
	data->mlx = mlx_init();
	if (!data->mlx)
		exit_error("Error: Unable to initialize mlx", data->map);
	data->win = mlx_new_window(data->mlx, WINDOW_WIDTH, WINDOW_HEIGHT, "FdF");
	if (!data->win)
		exit_error("Error: Failed to create mlx window", data->map);
	data->img = mlx_new_image(data->mlx, WINDOW_WIDTH - MENU_WIDTH,
			WINDOW_HEIGHT);
	if (!data->img)
		exit_error("Error: Failed to create mlx image", data->map);
	data->adr = mlx_get_data_addr(data->img, &data->bpp, &data->size_line,
			&data->endian);
	data->zoom = 1;
	data->offset_x = 0;
	data->offset_y = 0;
	data->angle_x = 0.0f;
	data->angle_y = 0.0f;
	data->angle_z = 0.0f;
	data->altitude = 0.3f;
	data->projection = 0;
	data->mouse.is_pressed = 0;
	initial_zoom(data);
	center_map(data);
	return ;
}
