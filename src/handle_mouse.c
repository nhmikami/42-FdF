/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_mouse.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naharumi <naharumi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 17:14:04 by naharumi          #+#    #+#             */
/*   Updated: 2025/01/22 19:27:35 by naharumi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fdf.h"

int	handle_mouse_press(int button, int x, int y, t_data *data)
{
	if (button == 4)
		data->zoom += 1;
	else if (button == 5 && data->zoom > 1)
		data->zoom -= 1;
	else if (button == 1 || button == 3)
	{
		data->mouse.is_pressed = 1;
		data->mouse.button = button;
		data->mouse.prev_x = x;
		data->mouse.prev_y = y;
	}
	render_img(data);
	return (0);
}

int	handle_mouse_release(int button, int x, int y, t_data *data)
{
	(void)button;
	(void)x;
	(void)y;
	data->mouse.is_pressed = 0;
	return (0);
}

int	handle_mouse_move(int x, int y, t_data *data)
{
	int	dx;
	int	dy;

	if (data->mouse.is_pressed)
	{
		dx = x - data->mouse.prev_x;
		dy = y - data->mouse.prev_y;
		if (data->mouse.button == 1)
		{
			data->offset_x += dx;
			data->offset_y += dy;
		}
		else if (data->mouse.button == 3)
		{
			data->angle_x -= dy * 0.005;
			data->angle_y += dx * 0.005;
			data->angle_z -= dx * 0.005;
		}
		data->mouse.prev_x = x;
		data->mouse.prev_y = y;
		render_img(data);
	}
	return (0);
}
