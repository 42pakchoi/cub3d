/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_minimap_player.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sarchoi <sarchoi@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 10:28:45 by cpak              #+#    #+#             */
/*   Updated: 2022/08/22 02:28:20 by sarchoi          ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	put_minimap_player(void)
{
	t_game		*game;
	t_map		*map;
	t_point		line_start;
	t_point		line_end;

	game = get_game_struct();
	map = &game->map;
	line_start.x = (game->player.pos.x * map->minimap_tile_size) - (MINIMAP_PLAYER_SIZE / 2);
	line_start.y = (game->player.pos.y * map->minimap_tile_size) - (MINIMAP_PLAYER_SIZE / 2);
	line_end.x = (game->player.pos.x * map->minimap_tile_size) + (MINIMAP_PLAYER_SIZE / 2);
	line_end.y = (game->player.pos.y * map->minimap_tile_size) + (MINIMAP_PLAYER_SIZE / 2);
	put_image_rect(game->minimap, line_start, line_end, MINIMAP_PLAYER_COLOR);
	return (0);
}
