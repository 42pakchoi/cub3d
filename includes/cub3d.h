/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sarchoi <sarchoi@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/03 01:31:51 by sarchoi           #+#    #+#             */
/*   Updated: 2022/08/04 13:32:59 by sarchoi          ###   ########seoul.kr  */
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

typedef struct s_img
{
	void		*img_ptr;
	int			*addr;
	int			size_line;
	int			bits_per_pixel;
	int			endian;
}				t_img;

typedef struct s_objects
{
	void	*player;
	void	*collect;
	void	*wall;
	void	*exit;
}				t_objects;

typedef struct s_map
{
	t_list		*raw;
	char		**array;
	int			width;
	int			height;
	t_img		background;
	t_objects	objects;
}				t_map;

typedef struct s_game
{
	void		*mlx;
	void		*win;
	t_map		map;
	t_vector	player_pos;
	t_bool		is_gameend;
}				t_game;

t_game	*get_game_struct(void);

/*
** constants
**/

# define WINDOW_WIDTH 640
# define WINDOW_HEIGHT 480
# define MINIMAP_TILE_SIZE 50
# define MINIMAP_WALL_COLOR 0x00FF00
# define MINIMAP_FLOOR_COLOR 0x000000
# define MINIMAP_PLAYER_COLOR 0x0000FF

/*
** map characters
*/
# define MAP_PLAYER_N	'N'
# define MAP_PLAYER_S	'S'
# define MAP_PLAYER_E	'E'
# define MAP_PLAYER_W	'W'
# define MAP_EMPTY		'0'
# define MAP_WALL		'1'

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
void	draw_minimap();

#endif
