/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_minimap_tiles.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpak <cpak@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 02:53:00 by sarchoi           #+#    #+#             */
/*   Updated: 2022/08/30 16:30:04 by cpak             ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	calc_tile_points(t_point *i, t_point *tile_start, t_point *tile_end)
{
	t_game	*game;
	t_map	*map;

	game = get_game_struct();
	map = &game->map;
	tile_start->x = i->x * map->minimap_tile_size;
	tile_start->y = i->y * map->minimap_tile_size;
	tile_end->x = tile_start->x + map->minimap_tile_size;
	tile_end->y = tile_start->y + map->minimap_tile_size;
}

void	put_minimap_tiles(void)
{
	t_game	*game;
	t_map	*map;
	t_point	i;
	t_point	tile_start;
	t_point	tile_end;

	game = get_game_struct();
	map = &(game->map);
	i.y = 0;
	while (i.y < (int) map->height)
	{
		i.x = 0;
		while (i.x < (int) map->width)
		{
			calc_tile_points(&i, &tile_start, &tile_end);
			if (map->array[i.y][i.x] == MAP_WALL)
				put_image_rect(
					game->minimap, tile_start, tile_end, MINIMAP_WALL_COLOR);
			if (map->array[i.y][i.x] == MAP_WALL_FIRE)
				put_image_rect(
					game->minimap, tile_start, tile_end, MINIMAP_FIRE_COLOR);
			if (map->array[i.y][i.x] == MAP_DOOR)
				put_image_rect(
					game->minimap, tile_start, tile_end, MINIMAP_DOOR_COLOR);
			i.x++;
		}
		i.y++;
	}
}
