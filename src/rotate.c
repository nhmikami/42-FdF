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

static t_point	rotate_x(t_point p, float angle_x)
{
	t_point	rotated;

	rotated.x = p.x;
	rotated.y = p.y * cos(angle_x) - p.z * sin(angle_x);
	rotated.z = p.y * sin(angle_x) + p.z * cos(angle_x);
	rotated.color = p.color;
	return (rotated);
}

static t_point	rotate_y(t_point p, float angle_y)
{
	t_point	rotated;

	rotated.x = p.x * cos(angle_y) + p.z * sin(angle_y);
	rotated.y = p.y;
	rotated.z = -p.x * sin(angle_y) + p.z * cos(angle_y);
	rotated.color = p.color;
	return (rotated);
}

static t_point	rotate_z(t_point p, float angle_z)
{
	t_point	rotated;

	rotated.x = p.x * cos(angle_z) - p.y * sin(angle_z);
	rotated.y = p.x * sin(angle_z) + p.y * cos(angle_z);
	rotated.z = p.z;
	rotated.color = p.color;
	return (rotated);
}

t_point	rotate(t_point p, t_data *data)
{
	p = rotate_x(p, data->angle_x);
	p = rotate_y(p, data->angle_y);
	p = rotate_z(p, data->angle_z);
	return (p);
}
