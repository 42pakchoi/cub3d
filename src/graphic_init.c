/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphic_init.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpak <cpak@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/08 01:53:01 by sarchoi           #+#    #+#             */
/*   Updated: 2022/08/30 16:26:50 by sarchoi          ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	set_images(void)
{
	t_game	*game;
	t_map	*map;

	game = get_game_struct();
	map = &(game->map);
	game->minimap = make_mlx_image(
			(int)map->width * map->minimap_tile_size,
			(int)map->height * map->minimap_tile_size
			);
	game->screen = make_mlx_image(WINDOW_WIDTH, WINDOW_HEIGHT);
}

static void	set_texture_images(void)
{
	t_game	*game;
	t_map	*map;

	game = get_game_struct();
	map = &(game->map);
	map->textures.south = get_png_image(map->path_south_texture);
	map->textures.north = get_png_image(map->path_north_texture);
	map->textures.west = get_png_image(map->path_west_texture);
	map->textures.east = get_png_image(map->path_east_texture);
	map->textures.door = get_png_image(IMG_DOOR);
	map->textures.door_side = get_png_image(IMG_DOOR_SIDE);
	if (
		map->textures.south == NULL
		|| map->textures.north == NULL
		|| map->textures.west == NULL
		|| map->textures.east == NULL
		|| !set_fire_texture()
	)
		exit_with_error("Failed to load textures");
}

static void	calc_minimap(void)
{
	t_game	*game;
	t_map	*map;

	game = get_game_struct();
	map = &(game->map);
	if (MAX_MINIMAP_SIZE < (int)map->width * MINIMAP_TILE_SIZE)
		map->minimap_tile_size = MAX_MINIMAP_SIZE / (int)map->width;
	if (MAX_MINIMAP_SIZE < (int)map->height * MINIMAP_TILE_SIZE)
		map->minimap_tile_size = MAX_MINIMAP_SIZE / (int)map->height;
	else
		map->minimap_tile_size = MINIMAP_TILE_SIZE;
	if (map->minimap_tile_size < 1)
		map->minimap_tile_size = 1;
}

void	init_images(void)
{
	set_texture_images();
	calc_minimap();
	set_images();
}
