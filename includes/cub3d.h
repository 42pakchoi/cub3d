/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpak <cpak@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/03 01:31:51 by sarchoi           #+#    #+#             */
/*   Updated: 2022/08/28 15:45:45 by cpak             ###   ########seoul.kr  */
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
	int			width;
	int			height;
}				t_img;

typedef struct s_textures
{
	t_img	*north;
	t_img	*south;
	t_img	*west;
	t_img	*east;
	t_img	*door;
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

typedef struct s_key
{
	int			move[4];
	int			rotate;
	int			rotate_origin;
}				t_key;

typedef struct s_player
{
	char		character;
	t_vector	pos;
	t_vector	dir;
	t_vector	plane;
	t_key		key;
}				t_player;

typedef struct s_game
{
	void		*mlx;
	void		*win;
	t_map		map;
	t_img		*minimap;
	t_img		*screen;
	t_player	player;
	t_bool		is_gameend;
}				t_game;

typedef struct s_dda
{
	t_vector	player_pos;
	t_vector	ray_dir;
	t_vector	delta_dist;
	t_point		player_grid;
	t_point		step;
	t_vector	side_dist;
	int			wall_dir;
	float		wall_dist;
	float		wall_collision_point;
	int			is_door;
}				t_dda;

t_game	*get_game_struct(void);

/*
** constants
**/

# define PLAYER_SPEED			0.09
# define PLAYER_ROTATE_SPEED	5

# define WINDOW_WIDTH 640
# define WINDOW_HEIGHT 480
# define MINIMAP_TILE_SIZE 5
# define MINIMAP_WALL_COLOR 0x0000FFFF
# define MINIMAP_DOOR_COLOR 0x000080
# define MINIMAP_FLOOR_COLOR 0xAAFFFF00
# define MINIMAP_DIRLINE_COLOR 0xFFFFFF
# define MINIMAP_RAY_COLOR 0xFFFFFF
# define MINIMAP_PLAYER_COLOR 0xFF00FF
# define MINIMAP_PLAYER_SIZE 3

# define WALL_DIR_N			0
# define WALL_DIR_S			1
# define WALL_DIR_E			2
# define WALL_DIR_W			3

# define WALL_DOOR			4
# define WALL_DOOR_SIDE		5

# define COLLISION_NONE		0
# define COLLISION_HOZ		1
# define COLLISION_VER		2
# define COLLISION_CORNER	3

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
# define MAP_DOOR			'D'
# define MAP_DOOR_OPEN		'O'

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
# define KEY_SPACEBAR		49
# define CLOSE_BUTTON		17

# define KEY_INDEX_W		0
# define KEY_INDEX_S		1
# define KEY_INDEX_A		2
# define KEY_INDEX_D		3

/*
** functions
*/

void		update_minimap_frame(void);

int			draw_frame(void);
int			erase_minimap_dirline(void);
int			erase_minimap_fov(void);
int			erase_minimap_ray(void);
int			erase_minimap_player(void);

void		init_dda(t_dda *dda);
void		calc_collision_point(char **map_grid, t_dda *dda);

int			put_screen_wall(void);
int			put_screen_ceiling_floor(void);
void		put_minimap_floor(void);
void		put_minimap_tiles(void);
void		put_minimap_line(t_vector start, t_vector end, int color);
int			put_minimap_player(void);
int			put_minimap_ray(void);

/*
** minimap
*/
void	init_map(char *map_filepath);
int		parse_map(void);
int		read_textures(void);
int		read_colors(void);
int		read_map(void);
int		validate_map(void);
int		check_map_walls(void);

void	init_images(void);

/*
** utils/mlx_image
*/
void draw_rect_in_image(t_img *image, t_point *start, t_size *size, unsigned int color);
void put_pixel(t_img *image, int x, int y, int color);
void	fill_color_image(t_img *image, unsigned int color);
t_img	*make_mlx_image(int width, int height);
t_img	*get_png_image(char *filepath);
void	put_image(void *img_ptr, t_point *img_pos);

/*
** utils/draw_pixel
*/
void	draw_pixel(t_point point, int color);
void	draw_pixel_line(float m, t_point point, t_point dpoint, int color);
void	draw_pixel_rect(t_vector start, t_vector end, int color);

/*
** utils/get_image
*/
int	get_image_pixel(t_img *image, int x, int y);

/*
** utils/put_image
*/
void	put_image_pixel(t_img *image, int x, int y, int color);
void	put_image_line(t_img *image, float m, t_point point, t_point dpoint, int color);
void	put_image_rect(t_img *image, t_point start, t_point end, int color);

/*
** functions - hooks
*/

int			key_up(int keycode);
int			key_down(int keycode);
int			mouse_up(void);
int			mouse_down(int button, int x);
int			mouse_move(int x);

void		set_player(void);

/*
** functions - calc
*/

t_vector	calc_rotated_vector(t_vector v, int d);

/*
** functions - player
*/

void	init_player(void);
void	set_player(void);

#endif
