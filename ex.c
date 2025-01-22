#include "../inc/fdf.h"

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->adr + (y * data->size_line + x * (data->bpp / 8));
	*(unsigned int*)dst = color;
}

int main(void)
{
	void	*mlx;
	void	*mlx_win;
	t_data	img;

	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, 1920, 1080, "FdF");
	img.img = mlx_new_image(mlx, 1920, 1080);
	img.adr = mlx_get_data_addr(img.img, &img.bpp, &img.size_line,
								&img.endian);
	my_mlx_pixel_put(&img, 500, 500, 0x00FF0000);
	mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);
	mlx_loop(mlx);

}


/*int main() {
	void *mlx_ptr = mlx_init();
	if (!mlx_ptr) {
		perror("Error initializing MLX");
		return 1;
	}

	void *win_ptr = mlx_new_window(mlx_ptr, 600, 400, "Exemplo MLX");
	if (!win_ptr) {
		 perror("Error creating window");
		 return 1;
	 }

	mlx_pixel_put(mlx_ptr, win_ptr, 300, 200, 0x00FF00); // Desenha um pixel verde no centro
	mlx_loop(mlx_ptr);
	return 0;
}*/


/*void test_read_map(char *file)
{
	t_map *map;

	ft_printf("Testing map file: %s\n", file);
	map = read_map(file);
	if (!map)
	{
		ft_printf("Error: Could not read map from file: %s\n", file);
		return;
	}
	ft_printf("Map loaded successfully!\n");
	ft_printf("Width: %d, Height: %d\n", map->width, map->height);
	for (int y = 0; y < map->height; y++)
	{
		for (int x = 0; x < map->width; x++)
		{
			ft_printf("(%d, %d, %d, 0x%x) ", map->matrix[y][x].x, 
				map->matrix[y][x].y, map->matrix[y][x].z, 
				map->matrix[y][x].color);
		}
		ft_printf("\n");
	}
	free_map(map);
	free(map);
}*/
