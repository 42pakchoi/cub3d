/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_minimap_floor_bonus.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sarchoi <sarchoi@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 02:58:10 by sarchoi           #+#    #+#             */
/*   Updated: 2022/09/01 17:07:27 by sarchoi          ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

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
	bottom_right.x = map->width * map->minimap_tile_size;
	bottom_right.y = map->height * map->minimap_tile_size;
	put_image_rect(game->minimap, top_left, bottom_right, MINIMAP_FLOOR_COLOR);
}
