/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sarchoi <sarchoi@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/03 01:31:51 by sarchoi           #+#    #+#             */
/*   Updated: 2022/08/08 15:14:48 by sarchoi          ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <stdio.h>
# include <string.h>
# include <math.h>
# include "mlx.h"
# include "libft.h"
# include "get_next_line.h"

/*
** structs
**/

typedef int	t_bool;
# define FT_TRUE		1
# define FT_FALSE		0
typedef struct s_vector
{
	float		x;
	float		y;
}				t_vector;

typedef struct s_point
{
	int			x;
	int			y;
}				t_point;

typedef struct s_size
{
	int			w;
	int			h;
}				t_size;

typedef struct s_line
{
	t_vector	start;
	t_vector	end;
}				t_line;

typedef struct s_img
{
	void		*img_ptr;
	int			*addr;
	int			size_line;
	int			bits_per_pixel;
	int			endian;
}				t_img;

typedef struct s_textures
{
	void	*north;
	void	*south;
	void	*west;
	void	*east;
	t_img	floor;
	t_img	ceiling;
	t_img	*minimap_floor;
	t_img	*minimap_wall;
}				t_textures;

typedef struct s_map
{
	t_list		*raw;
	char		**array;
	int			is_walled;
	size_t		width;
	size_t		height;
	char		*path_north_texture;
	char		*path_south_texture;
	char		*path_west_texture;
	char		*path_east_texture;
	int			floor_color;
	int			ceiling_color;
	t_textures	textures;
}				t_map;

typedef struct s_game
{
	void		*mlx;
	void		*win;
	t_map		map;
	t_vector	player_pos;
	t_vector	player_mov;
	t_vector	player_dir;
	int			player_angl;
	t_line		fov;
	t_vector	ray_vec[20];
	t_bool		is_gameend;
}				t_game;

t_game	*get_game_struct(void);

/*
** constants
**/

# define WINDOW_WIDTH 640
# define WINDOW_HEIGHT 480
# define MINIMAP_TILE_SIZE 15
# define MINIMAP_WALL_COLOR 0x0000FFFF
# define MINIMAP_FLOOR_COLOR 0x00989898
# define MINIMAP_DIRLINE_COLOR 0xFFFFFF
# define MINIMAP_RAY_COLOR 0xFF0000
# define MINIMAP_PLAYER_COLOR 0x00FF00FF
# define MINIMAP_PLAYER_WIDTH 10
# define MINIMAP_PLAYER_HEIGHT 10

/*
** map characters
*/
# define MAP_PLAYER_N		'N'
# define MAP_PLAYER_S		'S'
# define MAP_PLAYER_E		'E'
# define MAP_PLAYER_W		'W'
# define MAP_EMPTY			'0'
# define MAP_WALL			'1'
# define MAP_OUTSIDE		' '
# define MAP_TEST_VISITED	'.'

/*
** keycodes
** ESC: exit
** ARROW KEYS: move player
** WASD: move player
** CLOSE_BUTTON: the red close button at window bar
*/
# define KEY_ESC			53
# define KEY_Q				12
# define KEY_W				13
# define KEY_A				0
# define KEY_S				1
# define KEY_D				2
# define KEY_ARROW_UP		126
# define KEY_ARROW_DOWN		125
# define KEY_ARROW_LEFT		123
# define KEY_ARROW_RIGHT	124
# define CLOSE_BUTTON		17

/*
** functions
*/

int			draw_frame(void);
int			draw_minimap_dirline(void);
int			draw_minimap_fov(void);
int			draw_minimap_player(void);
int			draw_minimap_ray(void);
int			erase_minimap_dirline(void);
int			erase_minimap_fov(void);
int			erase_minimap_ray(void);
int			erase_minimap_player(void);

void		draw_line(t_vector start, t_vector end, int color);
void		draw_rect(t_vector start, t_vector end, int color);

void		set_pixel(t_point point, int color);

/*
** minimap
*/
void	prepare_map(char *map_filepath);
int		parse_map(void);
int		read_textures(void);
int		read_colors(void);
int		read_map(void);
int		validate_map(void);
int		check_map_walls(void);

void	init_images(void);
void	put_minimap(void);
// void	draw_frame(void);

/*
** utils/mlx_image
*/
t_img	*make_mlx_image(int width, int height, int color);
void	*get_png_image(char *filepath);
void	put_image(void *img_ptr, t_vector *img_pos);

/*
** functions - hooks
*/

int			mouse_hook(int button, int x, int y);
int			key_down_hook(int keycode);
int			key_up_hook(int keycode);

/*
** functions - calc
*/

t_vector	calc_rotated_vector(t_vector v, int d);

#endif
