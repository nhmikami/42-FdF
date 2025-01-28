/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naharumi <naharumi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 17:10:36 by naharumi          #+#    #+#             */
/*   Updated: 2025/01/22 18:59:28 by naharumi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fdf.h"

static t_point	rotate_x(t_point p, t_data *data)
{
	t_point	rotated;

	rotated.x = p.x;
	rotated.y = p.y * cos(data->angle_x) - p.z * data->altitude
		* sin(data->angle_x);
	rotated.z = p.y * sin(data->angle_x) + p.z * data->altitude
		* cos(data->angle_x);
	rotated.color = p.color;
	return (rotated);
}

static t_point	rotate_y(t_point p, t_data *data)
{
	t_point	rotated;

	rotated.x = p.x * cos(data->angle_y) + p.z * data->altitude
		* sin(data->angle_y);
	rotated.y = p.y;
	rotated.z = -p.x * sin(data->angle_y) + p.z * data->altitude
		* cos(data->angle_y);
	rotated.color = p.color;
	return (rotated);
}

static t_point	rotate_z(t_point p, t_data *data)
{
	t_point	rotated;

	rotated.x = p.x * cos(data->angle_z) - p.y * sin(data->angle_z);
	rotated.y = p.x * sin(data->angle_z) + p.y * cos(data->angle_z);
	rotated.z = p.z * data->altitude;
	rotated.color = p.color;
	return (rotated);
}

t_point	rotate(t_point p, t_data *data)
{
	p = rotate_x(p, data);
	p = rotate_y(p, data);
	p = rotate_z(p, data);
	return (p);
}
