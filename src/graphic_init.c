/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphic_init.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sarchoi <sarchoi@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/08 01:53:01 by sarchoi           #+#    #+#             */
/*   Updated: 2022/08/24 15:04:28 by sarchoi          ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void set_images(void)
{
	t_game *game;
	t_map * map;

	game = get_game_struct();
	map = &(game->map);
	game->minimap = make_mlx_image(
		(int)map->width * MINIMAP_TILE_SIZE,
		(int)map->height * MINIMAP_TILE_SIZE
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
	if (map->textures.south == NULL || map->textures.north == NULL ||
		map->textures.west == NULL || map->textures.east == NULL)
	{
		// 이미지 처리에 문제가 발생한 경우
		printf("error\n");
		return ;
	}
}

void	init_images(void)
{
	set_texture_images();
	set_images();
}
