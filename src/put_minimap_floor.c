/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_minimap_floor.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sarchoi <sarchoi@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 02:58:10 by sarchoi           #+#    #+#             */
/*   Updated: 2022/08/22 03:00:32 by sarchoi          ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	put_minimap_floor(void)
{
	t_game	*game;
	t_map	*map;
	t_point	top_left;
	t_point	bottom_right;

	game = get_game_struct();
	map = &game->map;
	top_left.x = 0;
	top_left.y = 0;
	bottom_right.x = map->width * MINIMAP_TILE_SIZE;
	bottom_right.y = map->height * MINIMAP_TILE_SIZE;
	put_image_rect(
		map->textures.minimap_floor,
		top_left,
		bottom_right,
		MINIMAP_FLOOR_COLOR
	);
}
