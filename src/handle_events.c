/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_events.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naharumi <naharumi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 19:24:18 by naharumi          #+#    #+#             */
/*   Updated: 2025/01/22 19:27:26 by naharumi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fdf.h"

void	set_hooks(t_data *data)
{
	mlx_hook(data->win, 2, 1L << 0, handle_key, data);
	mlx_hook(data->win, 4, 1L << 2, handle_mouse_press, data);
	mlx_hook(data->win, 5, 1L << 3, handle_mouse_release, data);
	mlx_hook(data->win, 6, 1L << 6, handle_mouse_move, data);
	mlx_hook(data->win, 17, 0, close_window, data);
	return ;
}

int	close_window(t_data *data)
{
	if (data->img)
		mlx_destroy_image(data->mlx, data->img);
	if (data->win)
		mlx_destroy_window(data->mlx, data->win);
	if (data->mlx)
	{
		mlx_destroy_display(data->mlx);
		free(data->mlx);
	}
	free_map(data->map);
	exit(EXIT_SUCCESS);
	return (0);
}

void	render_img(t_data *data)
{
	ft_bzero(data->adr, (WINDOW_WIDTH - MENU_WIDTH)
		* WINDOW_HEIGHT * (data->bpp / 8));
	draw_map(data);
	mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
	return ;
}
