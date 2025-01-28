/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naharumi <naharumi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 10:51:02 by naharumi          #+#    #+#             */
/*   Updated: 2025/01/24 10:55:35 by naharumi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <fcntl.h>
# include <limits.h>
# include <math.h>
# include <stdlib.h>
# include <unistd.h>
# include "../lib/libft.h"
# include "../minilibx-linux/mlx.h"

# define WINDOW_WIDTH 1280
# define WINDOW_HEIGHT 720
# define MENU_WIDTH 150

# define ESC_KEY 65307
# define LEFT_KEY 65361
# define UP_KEY 65362
# define RIGHT_KEY 65363
# define DOWN_KEY 65364
# define PLUS_KEY 61
# define MINUS_KEY 45
# define P_KEY 112
# define I_KEY 105
# define T_KEY 116
# define F_KEY 102
# define R_KEY 114
# define A_KEY 97
# define D_KEY 100
# define W_KEY 119
# define S_KEY 115
# define E_KEY 101
# define Q_KEY 113
# define X_KEY 120
# define Z_KEY 122

typedef struct s_point
{
	float	x;
	float	y;
	float	z;
	int		color;
}	t_point;

typedef struct s_map
{
	int		width;
	int		height;
	t_point	**matrix;
}	t_map;

typedef struct s_mouse
{
	int	prev_x;
	int	prev_y;
	int	is_pressed;
	int	button;
}	t_mouse;

typedef struct s_data
{
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
	float	altitude;
	t_mouse	mouse;
}	t_data;

typedef struct s_params
{
	float	x;
	float	y;
	float	dx;
	float	dy;
	float	steps;
	float	x_increment;
	float	y_increment;
	float	ratio;
}	t_params;

typedef struct s_bounds
{
	float	min_x;
	float	max_x;
	float	min_y;
	float	max_y;
}	t_bounds;

// initializing
t_map	*read_map(char *file);
int		fill_matrix(t_map *map, int fd);
void	init_data(t_data *data);

// draw map
void	draw_map(t_data *data);
t_point	rotate(t_point p, t_data *data);
t_point	project_point(t_point p, t_data *data);
t_point	project_isometric(t_point p);
t_point	project_parallel(t_point p);
t_point	project_top(t_point p);
t_point	project_front(t_point p);
t_point	project_right(t_point p);

// handle events
void	set_hooks(t_data *data);
void	render_img(t_data *data);
int		handle_key(int key, t_data *data);
int		handle_mouse(int button, int x, int y, t_data *data);
int		handle_mouse_press(int button, int x, int y, t_data *data);
int		handle_mouse_release(int button, int x, int y, t_data *data);
int		handle_mouse_move(int x, int y, t_data *data);
int		close_window(t_data *data);

// utils
int		check_extension(char *file);
int		free_and_return(char **arr, char *str);
void	free_map(t_map *map);
void	clear_gnl(int fd);
void	exit_error(char *msg, t_map *map);

#endif