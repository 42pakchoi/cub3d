/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_minimap_player.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpak <cpak@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 10:28:45 by cpak              #+#    #+#             */
/*   Updated: 2022/08/16 16:22:04 by cpak             ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	draw_minimap_player(void)
{
	t_game		*game;
	t_line		line;

	game = get_game_struct();
	line.start = game->player.pos;
	line.end = game->player.pos;
	line.start.x = (line.start.x * MINIMAP_TILE_SIZE) - (MINIMAP_PLAYER_SIZE / 2);
	line.start.y = (line.start.y * MINIMAP_TILE_SIZE) - (MINIMAP_PLAYER_SIZE / 2);
	line.end.x = (line.end.x * MINIMAP_TILE_SIZE) + (MINIMAP_PLAYER_SIZE / 2);
	line.end.y = (line.end.y * MINIMAP_TILE_SIZE) + (MINIMAP_PLAYER_SIZE / 2);
	draw_rect(line.start, line.end, MINIMAP_PLAYER_COLOR);
	return (0);
}
