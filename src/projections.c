/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projections.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naharumi <naharumi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 18:55:16 by naharumi          #+#    #+#             */
/*   Updated: 2025/01/22 19:42:16 by naharumi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fdf.h"

t_point	project_isometric(t_point p)
{
	t_point	proj;

	proj.x = (p.x - p.y) * cos(M_PI / 6);
	proj.y = (p.x + p.y) * sin(M_PI / 6) - p.z;
	return (proj);
}

t_point	project_parallel(t_point p)
{
	t_point	proj;

	proj.x = p.x;
	proj.y = p.y - p.z;
	return (proj);
}

t_point	project_top(t_point p)
{
	t_point	proj;

	proj.x = p.x;
	proj.y = p.y;
	return (proj);
}

t_point	project_front(t_point p)
{
	t_point	proj;

	proj.x = p.x;
	proj.y = -p.z;
	return (proj);
}

t_point	project_right(t_point p)
{
	t_point	proj;

	proj.x = -p.y;
	proj.y = -p.z;
	return (proj);
}
