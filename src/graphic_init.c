/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphic_init.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sarchoi <sarchoi@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/08 01:53:01 by sarchoi           #+#    #+#             */
/*   Updated: 2022/08/17 15:12:27 by sarchoi          ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	set_minimap_images(void)
{
	t_game	*game;
	t_map	*map;

	game = get_game_struct();
	map = &(game->map);
	map->textures.minimap_floor = make_mlx_image(
		(int)map->width * MINIMAP_TILE_SIZE,
		(int)map->height * MINIMAP_TILE_SIZE,
		MINIMAP_FLOOR_COLOR
	);
	map->textures.minimap_wall = make_mlx_image(
		MINIMAP_TILE_SIZE,
		MINIMAP_TILE_SIZE,
		MINIMAP_WALL_COLOR
	);
}

void	init_images(void)
{
	set_minimap_images();
}
