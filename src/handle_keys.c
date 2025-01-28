/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_keys.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naharumi <naharumi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 17:11:02 by naharumi          #+#    #+#             */
/*   Updated: 2025/01/24 11:05:49 by naharumi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fdf.h"

static void	handle_projection(int key, t_data *data)
{
	if (key == I_KEY || key == P_KEY || key == T_KEY
		|| key == F_KEY || key == R_KEY)
	{
		data->angle_x = 0;
		data->angle_y = 0;
		data->angle_z = 0;
	}
	if (key == I_KEY)
		data->projection = 0;
	else if (key == P_KEY)
		data->projection = 1;
	else if (key == T_KEY)
		data->projection = 2;
	else if (key == F_KEY)
		data->projection = 3;
	else if (key == R_KEY)
		data->projection = 4;
	return ;
}

static void	handle_zoom(int key, t_data *data)
{
	if (key == PLUS_KEY)
		data->zoom += 1;
	else if (key == MINUS_KEY && data->zoom > 1)
		data->zoom -= 1;
	else if (key == X_KEY)
		data->altitude += 0.1;
	else if (key == Z_KEY)
		data->altitude -= 0.1;
	return ;
}

static void	handle_move(int key, t_data *data)
{
	if (key == LEFT_KEY)
		data->offset_x -= 10;
	else if (key == UP_KEY)
		data->offset_y -= 10;
	else if (key == RIGHT_KEY)
		data->offset_x += 10;
	else if (key == DOWN_KEY)
		data->offset_y += 10;
	return ;
}

static void	handle_rotation(int key, t_data *data)
{
	if (key == W_KEY)
		data->angle_x += 0.1;
	else if (key == S_KEY)
		data->angle_x -= 0.1;
	else if (key == A_KEY)
		data->angle_y -= 0.1;
	else if (key == D_KEY)
		data->angle_y += 0.1;
	else if (key == E_KEY)
		data->angle_z -= 0.1;
	else if (key == Q_KEY)
		data->angle_z += 0.1;
	return ;
}

int	handle_key(int key, t_data *data)
{
	if (key == ESC_KEY)
		close_window(data);
	handle_projection(key, data);
	handle_zoom(key, data);
	handle_move(key, data);
	handle_rotation(key, data);
	render_img(data);
	return (0);
}
