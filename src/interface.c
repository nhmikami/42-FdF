/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interface.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naharumi <naharumi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 19:31:25 by naharumi          #+#    #+#             */
/*   Updated: 2025/01/22 19:33:09 by naharumi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fdf.h"

static void	draw_menu(t_data *data)
{
	int	pos;
	int	w;
	int	line;

	w = 0xFFFFFF;
	pos = WINDOW_WIDTH - MENU_WIDTH + 10;
	line = WINDOW_HEIGHT;
	while (line)
	{
		mlx_pixel_put(data->mlx, data->win, pos - 10, line, w);
		line--;
	}
	mlx_string_put(data->mlx, data->win, pos, 25, w, "Close              ESC");
	mlx_string_put(data->mlx, data->win, pos, 50, w, "Zoom     +/- or scroll");
	mlx_string_put(data->mlx, data->win, pos, 75, w, "Move            arrows");
	mlx_string_put(data->mlx, data->win, pos, 95, w, "          right button");
	mlx_string_put(data->mlx, data->win, pos, 125, w, "Rotate     left button");
	mlx_string_put(data->mlx, data->win, pos, 150, w, "Rotate X           W/S");
	mlx_string_put(data->mlx, data->win, pos, 175, w, "Rotate Y           A/D");
	mlx_string_put(data->mlx, data->win, pos, 200, w, "Rotate Z           Q/E");
	mlx_string_put(data->mlx, data->win, pos, 225, w, "Parallel             P");
	mlx_string_put(data->mlx, data->win, pos, 250, w, "Isometric            I");
	mlx_string_put(data->mlx, data->win, pos, 275, w, "Top                  T");
	mlx_string_put(data->mlx, data->win, pos, 300, w, "Front                F");
	mlx_string_put(data->mlx, data->win, pos, 325, w, "Right                R");
}

void	draw_interface(t_data *data)
{
	draw_menu(data);
	draw_map(data);
	mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
}
