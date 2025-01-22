#include "../inc/fdf.h"

int handle_key(int key, t_data *data)
{
	// printf("Key code: %d\n", key);

	if (key == ESC_KEY) // ESC to exit
		close_window(data);

	// Projeção
	if (key == I_KEY) // 'i' for Isometric projection
		data->projection = 0;
	if (key == P_KEY) // 'p' for Parallel projection
		data->projection = 1;

	// Zoom
	if (key == PLUS_KEY) // '=' for Zoom in
		data->zoom += 1;
	if (key == MINUS_KEY && data->zoom > 5) // '-' for Zoom out
		data->zoom -= 1;

	// Movimentação
	if (key == LEFT_KEY) // Left arrow - move left
		data->offset_x -= 10;
	if (key == UP_KEY) // Up arrow - move up
		data->offset_y -= 10;
	if (key == RIGHT_KEY) // Right arrow - move right
		data->offset_x += 10;
	if (key == DOWN_KEY) // Down arrow - move down
		data->offset_y += 10;
	

	// Rotação no eixo X (W e S)
	if (key == W_KEY) // W for Rotate around X-axis (positive)
		data->angle_x += 0.1;
	if (key == S_KEY) // S for Rotate around X-axis (negative)
		data->angle_x -= 0.1;

	// Rotação no eixo Y (A e D)
	if (key == A_KEY) // A for Rotate around Y-axis (negative)
		data->angle_y -= 0.1;
	if (key == D_KEY) // D for Rotate around Y-axis (positive)
		data->angle_y += 0.1;

	// Rotação no eixo Z (Q e E)
	if (key == E_KEY) // Q for Rotate around Z-axis (negative)
		data->angle_z -= 0.1;
	if (key == Q_KEY) // E for Rotate around Z-axis (positive)
		data->angle_z += 0.1;
	render_img(data);
	return (0);
}

int handle_mouse(int button, int x, int y, t_data *data)
{
	(void)x;
	(void)y;

	if (button == 4)
		data->zoom += 1;
	else if (button == 5 && data->zoom > 5)
		data->zoom -= 1;
	render_img(data); // Redesenha a imagem após o zoom
	return (0);
}

int	handle_mouse_press(int button, int x, int y, t_data *data)
{
	if (button == 4)
		data->zoom += 1;
	else if (button == 5 && data->zoom > 5)
		data->zoom -= 1;
	else
	{
		data->mouse.is_pressed = 1;
		data->mouse.button = button;
		data->mouse.prev_x = x;
		data->mouse.prev_y = y;
	}
	render_img(data); // Redesenha a imagem após o zoom
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

int handle_mouse_move(int x, int y, t_data *data)
{
	int dx;
	int dy;

	if (data->mouse.is_pressed)
	{
		dx = x - data->mouse.prev_x;
		dy = y - data->mouse.prev_y;
		if (data->mouse.button == 1)
		{
			data->angle_x += dy * 0.005;
			data->angle_y += dx * 0.005;
		}
		else if (data->mouse.button == 3)
		{
			data->offset_x += dx;
			data->offset_y += dy;
		}
		data->mouse.prev_x = x;
		data->mouse.prev_y = y;
		render_img(data);
	}
	return (0);
}

int	close_window(t_data *data)
{
	if (data->img)
		mlx_destroy_image(data->mlx, data->img);
	if (data->win)
		mlx_destroy_window(data->mlx, data->win);
	if (data->mlx)
		free(data->mlx);
	free_map(data->map);
	exit(EXIT_SUCCESS);
	return (0);
}
