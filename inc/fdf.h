#ifndef FDF_H
# define FDF_H
# include <stdio.h> // APAGAR
# include <fcntl.h>
# include <limits.h>
# include <math.h>
# include <mlx.h>
# include <stdlib.h>
# include <unistd.h>
# include "../lib/libft.h"

# define WINDOW_WIDTH 1280 //1920
# define WINDOW_HEIGHT 720 //1080
# define MENU_WIDTH 150

# define ESC_KEY 65307
# define LEFT_KEY 65361
# define UP_KEY 65362
# define RIGHT_KEY 65363
# define DOWN_KEY 65364
# define PLUS_KEY 61
# define MINUS_KEY 45
# define I_KEY 105
# define P_KEY 112
# define A_KEY 97
# define D_KEY 100
# define W_KEY 119
# define S_KEY 115
# define E_KEY 101
# define Q_KEY 113

typedef struct s_point {
	float	x;
	float	y;
	float	z;
	int		color; // Cor para gradiente (opcional)
} t_point;

typedef struct s_map {
	int		width;
	int		height;
	t_point	**matrix; // Matriz de pontos
} t_map;

typedef struct s_mouse
{
	int prev_x;
	int prev_y;
	int is_pressed; // 1 se o botão estiver pressionado, 0 caso contrário
	int button;     // Armazena o botão pressionado
} t_mouse;

typedef struct s_data {
	t_map	*map;
	void	*mlx;
	void	*win;
	void	*img;
	char	*adr;
	int		bpp;
	int		size_line;
	int		endian;
	int		zoom;
	int		offset_x;
	int		offset_y;
	int		projection;
	float	angle_x;
	float	angle_y;
	float	angle_z;
	t_mouse	mouse;
} t_data;

typedef struct s_params
{
	float	x;
	float	y;
	float	dx;
	float	dy;
	float	steps;
	float	x_increment;
	float	y_increment;
} t_params;

// read_map
t_map	*read_map(char *file);
/*int		init_map(t_map *map, char *file);
int		validate_map(t_map *map, char *file);
int		map_width(char *str);*/

// fill_matrix
int		fill_matrix(t_map *map, int fd);
/*int		fill_point(t_map *map, int x, int y, char *str);
int		get_color(char *str);
int		is_valid_color(char *str);
int		is_valid_int(char *str);*/

//draw_map
void 	draw_map(t_data *data);
t_point	project_point(t_point p, t_data *data);
void draw_menu(t_data *data);
int render_img(t_data *data);

// rotate
t_point	rotate_x(t_point p, float angle_x);
t_point	rotate_y(t_point p, float angle_y);
t_point	rotate_z(t_point p, float angle_z);

// utils
void	exit_error(char *msg, t_map *map);
void	free_map(t_map *map);
int		check_extension(char* file);
void	ft_bzero(void *s, size_t n);

// events
int 	handle_key(int key, t_data *data);
int		handle_mouse(int button, int x, int y, t_data *data);
int		handle_mouse_press(int button, int x, int y, t_data *data);
int		handle_mouse_release(int button, int x, int y, t_data *data);
int		handle_mouse_move(int x, int y, t_data *data);
int 	close_window(t_data *data);


#endif