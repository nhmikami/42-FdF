/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naharumi <naharumi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 17:10:21 by naharumi          #+#    #+#             */
/*   Updated: 2025/01/22 19:41:42 by naharumi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fdf.h"

t_point	project_point(t_point p, t_data *data)
{
	t_point	proj;

	p = rotate(p, data);
	proj.color = p.color;
	if (data->projection == 0)
		proj = project_isometric(p);
	else if (data->projection == 1)
		proj = project_parallel(p);
	else if (data->projection == 2)
		proj = project_top(p);
	else if (data->projection == 3)
		proj = project_front(p);
	else if (data->projection == 4)
		proj = project_right(p);
	proj.x = proj.x * data->zoom + data->offset_x;
	proj.y = proj.y * data->zoom + data->offset_y;
	return (proj);
}

static int	interpolate_color(int color1, int color2, float ratio)
{
	int	red;
	int	green;
	int	blue;
	int	color;

	red = ((color1 >> 16) & 0xFF) + ratio * (((color2 >> 16) & 0xFF)
			- ((color1 >> 16) & 0xFF));
	green = ((color1 >> 8) & 0xFF) + ratio * (((color2 >> 8) & 0xFF)
			- ((color1 >> 8) & 0xFF));
	blue = (color1 & 0xFF) + ratio * ((color2 & 0xFF)
			- (color1 & 0xFF));
	color = (red << 16) + (green << 8) + blue;
	return (color);
}

static void	draw_pixel(t_point p, t_data *data)
{
	char	*pixel;

	if (p.x >= 0 && p.x < (WINDOW_WIDTH - MENU_WIDTH)
		&& p.y >= 0 && p.y < WINDOW_HEIGHT)
	{
		pixel = data->adr + ((int)p.y * data->size_line
				+ (int)p.x * (data->bpp / 8));
		*(int *)pixel = p.color;
	}
	return ;
}

static void	draw_line(t_point p1, t_point p2, t_data *data)
{
	t_params	dda;
	int			i;

	dda.dx = p2.x - p1.x;
	dda.dy = p2.y - p1.y;
	if (fabs(dda.dx) > fabs(dda.dy))
		dda.steps = fabs(dda.dx);
	else
		dda.steps = fabs(dda.dy);
	if (dda.steps == 0)
		return ;
	dda.x_increment = dda.dx / dda.steps;
	dda.y_increment = dda.dy / dda.steps;
	dda.x = p1.x;
	dda.y = p1.y;
	i = 0;
	while (i <= dda.steps)
	{
		dda.ratio = (float)i / dda.steps;
		draw_pixel((t_point){round(dda.x), round(dda.y), 0,
			interpolate_color(p1.color, p2.color, dda.ratio)}, data);
		dda.x += dda.x_increment;
		dda.y += dda.y_increment;
		i++;
	}
}

void	draw_map(t_data *data)
{
	int	x;
	int	y;

	y = 0;
	while (y < data->map->height)
	{
		x = 0;
		while (x < data->map->width)
		{
			if (x < data->map->width - 1)
				draw_line(
					project_point(data->map->matrix[y][x], data),
					project_point(data->map->matrix[y][x + 1], data), data);
			if (y < data->map->height - 1)
				draw_line(
					project_point(data->map->matrix[y][x], data),
					project_point(data->map->matrix[y + 1][x], data), data);
			x++;
		}
		y++;
	}
	return ;
}
