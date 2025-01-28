/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naharumi <naharumi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 17:09:58 by naharumi          #+#    #+#             */
/*   Updated: 2025/01/24 11:53:10 by naharumi         ###   ########.fr       */
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
	while (line--)
		mlx_pixel_put(data->mlx, data->win, pos - 10, line, w);
	mlx_string_put(data->mlx, data->win, pos, 25, w, "Close              ESC");
	mlx_string_put(data->mlx, data->win, pos, 50, w, "Zoom     +/- or scroll");
	mlx_string_put(data->mlx, data->win, pos, 75, w, "Move            arrows");
	mlx_string_put(data->mlx, data->win, pos, 95, w, "           left button");
	mlx_string_put(data->mlx, data->win, pos, 125, w, "Rotate    right button");
	mlx_string_put(data->mlx, data->win, pos, 150, w, "Rotate X           W/S");
	mlx_string_put(data->mlx, data->win, pos, 175, w, "Rotate Y           A/D");
	mlx_string_put(data->mlx, data->win, pos, 200, w, "Rotate Z           Q/E");
	mlx_string_put(data->mlx, data->win, pos, 225, w, "Altitude           Z/X");
	mlx_string_put(data->mlx, data->win, pos, 250, w, "Parallel             P");
	mlx_string_put(data->mlx, data->win, pos, 275, w, "Isometric            I");
	mlx_string_put(data->mlx, data->win, pos, 300, w, "Top                  T");
	mlx_string_put(data->mlx, data->win, pos, 325, w, "Front                F");
	mlx_string_put(data->mlx, data->win, pos, 350, w, "Right                R");
	return ;
}

static void	draw_interface(t_data *data)
{
	draw_menu(data);
	render_img(data);
	return ;
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
