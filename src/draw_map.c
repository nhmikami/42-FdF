#include "../inc/fdf.h"

t_point project_point(t_point p, t_data *data)
{
	t_point proj;

	p = rotate_x(p, data->angle_x);
	p = rotate_y(p, data->angle_y);
	p = rotate_z(p, data->angle_z);
	proj.color = p.color;
	if (data->projection == 0)
	{
		proj.x = (p.x - p.y) * cos(M_PI / 6);
		proj.y = (p.x + p.y) * sin(M_PI / 6) - p.z;
	}
	else if (data->projection == 1)
	{
		proj.x = p.x;
		proj.y = p.y - p.z;
	}
	proj.x = proj.x * data->zoom + data->offset_x;
	proj.y = proj.y * data->zoom + data->offset_y;
	return (proj);
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

static void draw_line(t_point p1, t_point p2, t_data *data)
{
	t_params	dda;
	int			i;

	dda.dx = p2.x - p1.x;
	dda.dy = p2.y - p1.y;
	if (fabs(dda.dx) > fabs(dda.dy))
		dda.steps = fabs(dda.dx);
	else
		dda.steps = fabs(dda.dy);
	if(dda.steps == 0)
		return;
	dda.x_increment = dda.dx / dda.steps;
	dda.y_increment = dda.dy / dda.steps;
	dda.x = p1.x;
	dda.y = p1.y;
	i = 0;
	while (i <= dda.steps)
	{
		draw_pixel((t_point){round(dda.x), round(dda.y), 0, p1.color}, data);
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

/*static void	bresenham(t_params *params)
{
	int	e2;

	e2 = 2 * (params->err);
	if (e2 > -(params->dy))
	{
		params->err -= params->dy;
		if (params->p1.x < params->p2.x)
			params->p1.x += 1;
		else
			params->p1.x -= 1;
	}
	if (e2 < params->dx)
	{
		params->err += params->dx;
		if (params->p1.y < params->p2.y)
			params->p1.y += 1;
		else
			params->p1.y -= 1;
	}
	return ;
}

static void	draw_line(t_point p1, t_point p2, t_data *data)
{
	t_params	params;

	params.dx = fabs(p2.x - p1.x);
	params.dy = fabs(p2.y - p1.y);
	params.err = params.dx - params.dy;
	params.p1 = p1;
	params.p2 = p2;
	while (1)
	{
		if (params.p1.x < 0 || params.p1.x >= WINDOW_WIDTH - MENU_WIDTH ||
			   params.p1.y < 0 || params.p1.y >= WINDOW_HEIGHT)
			   break;
		draw_pixel(params.p1, data);
		if ((int)round(params.p1.x) == (int)round(params.p2.x)
			&& (int)round(params.p1.y) == (int)round(params.p2.y))
			break ;
		bresenham(&params);
	}
	return ;
}*/



/*static int interpolate_color(int color1, int color2, double t)
{
	int r1 = (color1 >> 16) & 0xFF;
	int g1 = (color1 >> 8) & 0xFF;
	int b1 = color1 & 0xFF;

	int r2 = (color2 >> 16) & 0xFF;
	int g2 = (color2 >> 8) & 0xFF;
	int b2 = color2 & 0xFF;

	int r = r1 + (r2 - r1) * t;
	int g = g1 + (g2 - g1) * t;
	int b = b1 + (b2 - b1) * t;
	
	return (r << 16) | (g << 8) | b;
}

static void	draw_line(t_point p1, t_point p2, t_data *data)
{
	t_params params;
	int		line_len;
	double   t;

	params.dx = fabs(p2.x - p1.x);
	params.dy = fabs(p2.y - p1.y);
	params.err = params.dx - params.dy;
	params.p1 = p1;
	params.p2 = p2;
	line_len = sqrt(params.dx * params.dx + params.dy * params.dy);

	int step = 0;
	while (1)
	{
		if (line_len > 0)
			t = (double)step / (double)line_len;
		else
			t = 0;
		params.p1.color = interpolate_color(p1.color, p2.color, t);

		draw_pixel(params.p1, data);
		if ((int)round(params.p1.x) == (int)round(params.p2.x)
			&& (int)round(params.p1.y) == (int)round(params.p2.y))
			break ;
		bresenham(&params);
		step++;
	}
}*/


/*t_point project_point(t_point point, t_data *data)
{
	t_point projected;
	float x, y, z;
	float temp_x, temp_y, temp_z;

	x = point.x * data->zoom - data->map->width * data->zoom / 2;
	y = point.y * data->zoom - data->map->height * data->zoom / 2;
	z = point.z * data->zoom;

	// Rotation around X-axis
	temp_y = y * cos(data->angle_x) - z * sin(data->angle_x);
	temp_z = y * sin(data->angle_x) + z * cos(data->angle_x);
	y = temp_y;
	z = temp_z;

	// Rotation around Y-axis
	temp_x = x * cos(data->angle_y) + z * sin(data->angle_y);
	temp_z = -x * sin(data->angle_y) + z * cos(data->angle_y);
	x = temp_x;
	z = temp_z;

	// Rotation around Z-axis
	temp_x = x * cos(data->angle_z) - y * sin(data->angle_z);
	temp_y = x * sin(data->angle_z) + y * cos(data->angle_z);
	x = temp_x;
	y = temp_y;

	if (data->projection == 0) // Isometric
	{
		projected.x = (x - y) * cos(M_PI / 6) + data->offset_x;
		projected.y = (x + y) * sin(M_PI / 6) - z + data->offset_y;
	}
	else if (data->projection == 1) // Parallel
	{
		projected.x = x + data->offset_x;
		projected.y = y - z + data->offset_y;
	}
	else if (data->projection == 2) // Top view
	{
		projected.x = x + data->offset_x;
		projected.y = y + data->offset_y;
	}
	else if (data->projection == 3) // Side view (Right)
	{
		projected.x = z + data->offset_x;
		projected.y = y + data->offset_y;
	}
	else if (data->projection == 4) // Front view
	{
		projected.x = x + data->offset_x;
		projected.y = z + data->offset_y;
	}
	
	projected.color = point.color;
	return projected;
}*/
