/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpak <cpak@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/03 01:31:51 by sarchoi           #+#    #+#             */
/*   Updated: 2022/09/01 20:52:50 by cpak             ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_BONUS_H
# define CUB3D_BONUS_H

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <stdio.h>
# include <math.h>
# include "mlx.h"
# include "libft.h"
# include "get_next_line.h"

/*
** structs
**/

typedef int			t_bool;
# define FT_TRUE	1
# define FT_FALSE	0

typedef struct s_vector
{
	float			x;
	float			y;
}					t_vector;

typedef struct s_point
{
	int				x;
	int				y;
}					t_point;

typedef struct s_size
{
	int				w;
	int				h;
}					t_size;

typedef struct s_line
{
	t_vector		start;
	t_vector		end;
}					t_line;

typedef struct s_img
{
	void			*img_ptr;
	int				*addr;
	int				size_line;
	int				bits_per_pixel;
	int				endian;
	int				width;
	int				height;
}					t_img;

typedef struct s_textures
{
	t_img			*north;
	t_img			*south;
	t_img			*west;
	t_img			*east;
	t_img			*door;
	t_img			*door_side;
	t_img			**fire;
	t_img			*minimap_floor;
	t_img			*minimap_wall;
}					t_textures;

typedef struct s_map
{
	t_list			*raw;
	char			**array;
	int				is_walled;
	size_t			width;
	size_t			height;
	char			*path_north_texture;
	char			*path_south_texture;
	char			*path_west_texture;
	char			*path_east_texture;
	int				floor_color;
	int				ceiling_color;
	unsigned int	minimap_tile_size;
	float			sprite_count;
	t_textures		textures;
}					t_map;

typedef struct s_key
{
	int				move[4];
	int				rotate;
	int				rotate_origin;
}					t_key;

typedef struct s_player
{
	char			character;
	t_vector		pos;
	t_vector		dir;
	t_vector		plane;
	t_key			key;
}					t_player;

typedef struct s_game
{
	void			*mlx;
	void			*win;
	t_map			map;
	t_img			*minimap;
	t_img			*screen;
	t_img			*sprite;
	t_player		player;
}					t_game;

typedef struct s_dda
{
	t_vector		player_pos;
	t_vector		ray_dir;
	t_vector		delta_dist;
	t_point			player_grid;
	t_point			step;
	t_vector		side_dist;
	int				wall_dir;
	float			wall_dist;
	float			wall_collision_point;
	int				is_door;
	int				is_fire;
}					t_dda;

typedef struct s_bres
{
	t_point			point;
	t_size			size;
	float			m;
	int				max;
}					t_bres;

/*
** constants
**/

# define PLAYER_SPEED			0.09
# define PLAYER_ROTATE_SPEED	5

# define WINDOW_WIDTH			640
# define WINDOW_HEIGHT			480
# define MINIMAP_TILE_SIZE		5
# define MAX_MINIMAP_SIZE		100
# define MINIMAP_WALL_COLOR		0xAA00A500
# define MINIMAP_FIRE_COLOR		0xAA77ff77
# define MINIMAP_DOOR_COLOR		0xAAFF2600
# define MINIMAP_FLOOR_COLOR	0x55111111
# define MINIMAP_DIRLINE_COLOR	0xFFFFFF
# define MINIMAP_RAY_COLOR		0xEEAAAAAA
# define MINIMAP_PLAYER_COLOR	0x00FFFF
# define MINIMAP_PLAYER_SIZE	3

# define WALL_DIR_N			0
# define WALL_DIR_S			1
# define WALL_DIR_E			2
# define WALL_DIR_W			3

# define WALL_DOOR			4
# define WALL_DOOR_SIDE		5
# define WALL_FIRE			6

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
# define MAP_WALL_FIRE		'2'
# define MAP_OUTSIDE		' '
# define MAP_TEST_VISITED	'.'
# define MAP_DOOR			'D'
# define MAP_DOOR_OPEN		'O'

/*
** Image Paths
*/
# define IMG_DOOR		"./textures/dungeon_door.png"
# define IMG_DOOR_SIDE	"./textures/dungeon_door_side.png"
# define PREFIX_IMG_FIRE		"./textures/fireplace/fire-"
# define IMG_FIRE_FRAME			19

/*
** keycodes
** ESC: exit
** WASD: move player
** ARROW KEYS: move player's view
** CLOSE_BUTTON: the red close button at window bar
*/
# define KEY_ESC			53
# define KEY_W				13
# define KEY_A				0
# define KEY_S				1
# define KEY_D				2
# define KEY_ARROW_LEFT		123
# define KEY_ARROW_RIGHT	124
# define KEY_SPACEBAR		49

# define KEY_INDEX_W		0
# define KEY_INDEX_S		1
# define KEY_INDEX_A		2
# define KEY_INDEX_D		3

/*
** x_event refers from X.h
*/
# define KEY_PRESS			2
# define KEY_RELEASE		3
# define BUTTON_PRESS		4
# define BUTTON_RELEASE		5
# define MOTION_NOTIFY		6
# define CLOSE_BUTTON		17

/*
** functions
*/

void		init_player(void);
void		rotate_player(t_game *game, int angle);
void		set_player(void);

void		init_images(void);
void		put_minimap_floor(void);
void		put_minimap_line(t_vector start, t_vector end);
int			put_minimap_player(void);
int			put_minimap_ray(void);
void		put_minimap_tiles(void);
int			put_screen_wall(void);
int			put_screen_ceiling_floor(void);

void		init_map(char *map_filepath);
int			read_map(void);
int			read_colors(void);
int			read_textures(void);
t_list		*find_map_line(t_list *head, char *to_find);
int			parse_map(void);
t_list		*find_map_start_line(void);
char		**get_map_array(t_list *map_start_line, size_t h, size_t w);

int			validate_map(void);
int			check_map_characters(void);
int			check_map_required_characters(void);
int			check_map_walls(void);
int			check_map_empty_line(void);
int			is_player_char(char c);

void		bres_algo(t_bres bres, int is_sub);
t_vector	calc_rotated_vector(t_vector v, int d);

int			key_up(int keycode);
int			key_down(int keycode);
int			mouse_up(void);
int			mouse_down(int button, int x);
int			mouse_move(int x);

int			draw_frame(void);
void		free_game(void);

/*
**	utils
*/
t_game		*get_game_struct(void);

void		print_info(char *message);
int			print_error(char *message);

void		exit_with_error(char *message);
int			exit_with_close_button(void);

void		calc_collision_point(char **map_grid, t_dda *dda);
void		init_dda(t_dda *dda);
void		calc_dda(t_dda *dda);

void		fill_color_image(t_img *image, unsigned int color);
t_img		*make_mlx_image(int width, int height);
t_img		*get_png_image(char *filepath);
void		put_image(void *img_ptr, t_point *img_pos);

int			get_image_pixel(t_img *image, int x, int y);
void		put_image_pixel(t_img *image, int x, int y, int color);
void		put_image_rect(t_img *image, t_point start, t_point end, int color);

void		draw_pixel(t_point point, int color);
void		draw_pixel_line(float m, t_point point, t_point dpoint, int color);
void		draw_pixel_rect(t_vector start, t_vector end, int color);

int			set_fire_texture(void);

#endif
