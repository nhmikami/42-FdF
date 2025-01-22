#include "../inc/fdf.h"

// events
void	draw_menu(t_data *data)
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
	mlx_string_put(data->mlx, data->win, pos, 25, w, "Close : Esc");
	mlx_string_put(data->mlx, data->win, pos, 50, w, "Move : arrows");
	mlx_string_put(data->mlx, data->win, pos, 75, w, "Zoom : scroll or +/-");
	mlx_string_put(data->mlx, data->win, pos, 100, w, "Rotate X : W/S");
	mlx_string_put(data->mlx, data->win, pos, 125, w, "Rotate Y : A/D");
	mlx_string_put(data->mlx, data->win, pos, 150, w, "Rotate Z : Q/E");
	mlx_string_put(data->mlx, data->win, pos, 175, w, "Isometric : I");
	mlx_string_put(data->mlx, data->win, pos, 200, w, "Parallel : P");
	//mlx_string_put(data->mlx, data->win, pos, 225, w, "3D Depth : M/N");
	//mlx_string_put(data->mlx, data->win, pos, 250, w, "Color White : Click");
}

int render_img(t_data *data)
{	
	ft_bzero(data->adr, (WINDOW_WIDTH - MENU_WIDTH) * WINDOW_HEIGHT * (data->bpp / 8)); // Limpa a tela
	// draw_menu(data); // Desenha o menu
	draw_map(data);  // Desenha o map
	mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0); // Atualiza a janela
}

// initializing mlx
static void calculate_initial_zoom(t_data *data)
{
	float width_zoom;
	float height_zoom;
	float rotated_width;
	float rotated_height;

	rotated_width = fabs(data->map->width * cos(data->angle_z)) + fabs(data->map->height * sin(data->angle_z));
	rotated_height = fabs(data->map->width * sin(data->angle_z)) + fabs(data->map->height * cos(data->angle_z));
	width_zoom = (float)WINDOW_WIDTH / rotated_width;
	height_zoom = (float)WINDOW_HEIGHT / rotated_height;
	if (width_zoom < height_zoom)
		data->zoom = width_zoom;
	else
		data->zoom = height_zoom;
	if (data->zoom < 5)
		data->zoom = 5;
	if (data->zoom > 15)
		data->zoom = 15;
	printf("zoom = %d\n", data->zoom);
}

static void center_map(t_data *data)
{
	float rotated_width;
	float rotated_height;

	rotated_width = fabs(data->map->width * cos(data->angle_z)) + fabs(data->map->height * sin(data->angle_z));
	rotated_height = fabs(data->map->width * sin(data->angle_z)) + fabs(data->map->height * cos(data->angle_z));
	data->offset_x = (WINDOW_WIDTH - (rotated_width * data->zoom)) / 2;
	data->offset_y = (WINDOW_HEIGHT - (rotated_height * data->zoom)) / 2;
	if (data->offset_x < 0)
		data->offset_x = 0;
	if (data->offset_y < 0)
		data->offset_y = 0;

	printf("offset x = %d, offset y = %d\n", data->offset_x, data->offset_y);
}

void	init_data(t_data *data)
{
	data->mlx = mlx_init();
	if (!data->mlx)
		exit_error("Error: Unable to initialize mlx", data->map);
	data->win = mlx_new_window(data->mlx, WINDOW_WIDTH, WINDOW_HEIGHT, "FdF");
	data->img = mlx_new_image(data->mlx, WINDOW_WIDTH - MENU_WIDTH, WINDOW_HEIGHT);
	data->adr = mlx_get_data_addr(data->img, &data->bpp, &data->size_line, &data->endian);
	data->angle_x = 0;
	data->angle_y = 0;
	data->angle_z = 0;
	data->projection = 0;
	data->mouse.is_pressed = 0;
	data->offset_x = (WINDOW_WIDTH - MENU_WIDTH) / 2;
	data->offset_y = 0;
	calculate_initial_zoom(data);
	center_map(data);
}

int main(int ac, char **av)
{
	t_data  data;

	if (ac != 2)
		exit_error("Usage: ./fdf <map_file.fdf>", NULL);
	if(!check_extension(av[1]))
		exit_error("Error: Invalid file extension", NULL);
	data.map = read_map(av[1]);
	if (!data.map)
		exit_error("Error: Unable to load map", NULL);
	init_data(&data);
	draw_menu(&data);
	draw_map(&data);
	mlx_put_image_to_window(data.mlx, data.win, data.img, 0, 0);

	//mlx_mouse_hook(data.win, handle_mouse, &data);
	mlx_hook(data.win, 2, 1L << 0, handle_key, &data);
	mlx_hook(data.win, 4, 1L << 2, handle_mouse, &data);
	mlx_hook(data.win, 4, 1L << 2, handle_mouse_press, &data);   // Mouse Press
	mlx_hook(data.win, 5, 1L << 3, handle_mouse_release, &data); // Mouse Release
	mlx_hook(data.win, 6, 1L << 6, handle_mouse_move, &data);    // Mouse Move
	mlx_hook(data.win, 17, 0, close_window, &data);
	mlx_hook(data.win, 7, 1L << 04, render_img, &data);
	mlx_loop(data.mlx);
	free_map(data.map);
	return (0);
}

// gcc src/*.c lib/*.c -Iincludes -Iminilibx-linux -Lminilibx-linux -lmlx -lm -lXext -lX11 -o test


