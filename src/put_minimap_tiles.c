/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_minimap_tiles.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sarchoi <sarchoi@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 02:53:00 by sarchoi           #+#    #+#             */
/*   Updated: 2022/08/30 17:19:38 by sarchoi          ###   ########seoul.kr  */
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

static void	put_tile(char c, t_point *tile_start, t_point *tile_end)
{
	t_game	*game;

	game = get_game_struct();
	if (c == MAP_WALL)
		put_image_rect(
			game->minimap, *tile_start, *tile_end, MINIMAP_WALL_COLOR);
	if (c == MAP_WALL_FIRE)
		put_image_rect(
			game->minimap, *tile_start, *tile_end, MINIMAP_FIRE_COLOR);
	if (c == MAP_DOOR)
		put_image_rect(
			game->minimap, *tile_start, *tile_end, MINIMAP_DOOR_COLOR);
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
			put_tile(map->array[i.y][i.x], &tile_start, &tile_end);
			i.x++;
		}
		i.y++;
	}
}
