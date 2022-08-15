/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_minimap_player.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sarchoi <sarchoi@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 10:28:45 by cpak              #+#    #+#             */
/*   Updated: 2022/08/15 18:27:05 by sarchoi          ###   ########seoul.kr  */
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
	line.start.x *= MINIMAP_PLAYER_HEIGHT;
	line.start.y *= MINIMAP_PLAYER_WIDTH;
	line.end.x *= MINIMAP_PLAYER_HEIGHT;
	line.end.y *= MINIMAP_PLAYER_WIDTH;
	draw_rect(line.start, line.end, MINIMAP_PLAYER_COLOR);
	return (0);
}
